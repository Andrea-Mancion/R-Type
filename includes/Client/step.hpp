#include <iostream>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <vector>
#include <functional>
#include <any>
#include <exception>
#include <optional>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

struct Position {
    float x, y;
};

struct Velocity {
    float dx, dy;
};

struct Controllable {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
};

struct Drawanle {
    sf::Sprite sprites;
};

struct BulletTag {
    bool isBullet;

    BulletTag(bool isBullet) : isBullet(isBullet) {}
};

struct Timer {
    float elapsedTime = 0.0f;
    float shootInterval;

    Timer(float interval) : shootInterval(interval) {}
};

class entity {
    friend class Registry;

    private:
        size_t x;
    public:
        explicit entity(size_t x) : x(x) {}
        operator std::size_t() const { return x; }
};

template <typename Component>
class sparse_array {
public:
    using value_type = std::optional<Component>;
    using reference_type = value_type&;
    using const_reference_type = value_type const&;
    using container_t = std::vector<value_type>;
    using size_type = typename container_t::size_type;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

public:
    sparse_array();
    sparse_array(sparse_array const&);
    sparse_array(sparse_array&&) noexcept;
    ~sparse_array();
    sparse_array& operator=(sparse_array const&);
    sparse_array& operator=(sparse_array&&) noexcept;
    reference_type operator[](size_t idx);
    const_reference_type operator[](size_t idx) const;
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    size_type size() const;
    reference_type insert_at(size_type pos, Component const&);
    reference_type insert_at(size_type pos, Component&&);
    template <class... Params>
    reference_type emplace_at(size_type pos, Params&&...);
    void erase(size_type pos) {
        if (pos < _data.size()) {
            _data[pos] = std::nullopt;
        }
    };
    size_type get_index(value_type const&) const;
    reference_type get(entity entity);

private:
    container_t _data;
};

template <typename Component>
sparse_array<Component>::sparse_array() {}

template <typename Component>
sparse_array<Component>::sparse_array(sparse_array const& other) : _data(other._data) {}

template <typename Component>
sparse_array<Component>::sparse_array(sparse_array&& other) noexcept : _data(std::move(other._data)) {}

template <typename Component>
sparse_array<Component>::~sparse_array() {}

template <typename Component>
sparse_array<Component>& sparse_array<Component>::operator=(sparse_array const& other) {
    if (this != &other) {
        _data = other._data;
    }
    return *this;
}

template <typename Component>
sparse_array<Component>& sparse_array<Component>::operator=(sparse_array&& other) noexcept {
    if (this != &other) {
        _data = std::move(other._data);
    }
    return *this;
}

template <typename Component>
typename sparse_array<Component>::reference_type sparse_array<Component>::operator[](size_t idx) {
    return _data[idx];
}

template <typename Component>
typename sparse_array<Component>::const_reference_type sparse_array<Component>::operator[](size_t idx) const {
    return _data[idx];
}

template <typename Component>
typename sparse_array<Component>::iterator sparse_array<Component>::begin() {
    return _data.begin();
}

template <typename Component>
typename sparse_array<Component>::const_iterator sparse_array<Component>::begin() const {
    return _data.begin();
}

template <typename Component>
typename sparse_array<Component>::const_iterator sparse_array<Component>::cbegin() const {
    return _data.cbegin();
}

template <typename Component>
typename sparse_array<Component>::iterator sparse_array<Component>::end() {
    return _data.end();
}

template <typename Component>
typename sparse_array<Component>::const_iterator sparse_array<Component>::end() const {
    return _data.end();
}

template <typename Component>
typename sparse_array<Component>::const_iterator sparse_array<Component>::cend() const {
    return _data.cend();
}

template <typename Component>
typename sparse_array<Component>::size_type sparse_array<Component>::size() const {
    return _data.size();
}

template <typename Component>
typename sparse_array<Component>::reference_type sparse_array<Component>::insert_at(size_type pos, Component const& value) {
    if (pos >= _data.size()) {
        _data.resize(pos + 1);
    }
    _data[pos] = value;
    return _data[pos];
}

template <typename Component>
typename sparse_array<Component>::reference_type sparse_array<Component>::insert_at(size_type pos, Component&& value) {
    if (pos >= _data.size()) {
        _data.resize(pos + 1);
    }
    _data[pos] = std::move(value);
    return _data[pos];
}

template <typename Component>
template <class... Params>
typename sparse_array<Component>::reference_type sparse_array<Component>::emplace_at(size_type pos, Params&&... params) {
    if (pos >= _data.size()) {
        _data.resize(pos + 1);
    }

    // Destroy the existing object
    _data[pos].reset();

    // Construct the new object in-place
    _data[pos].emplace(std::forward<Params>(params)...);

    return _data[pos];
}

template <typename Component>
typename sparse_array<Component>::reference_type sparse_array<Component>::get(entity entity) {
    size_type pos = static_cast<size_type>(entity);
    if (pos < _data.size() && _data[pos].has_value()) {
        return _data[pos].value();
    } else {
        throw std::out_of_range("Entity not found");
    }
}

template <typename Component>
typename sparse_array<Component>::size_type sparse_array<Component>::get_index(value_type const& value) const {
    for (size_type i = 0; i < _data.size(); ++i) {
        if (_data[i] == value) {
            return i;
        }
    }
    return static_cast<size_type>(-1);  // Not found
}

struct EntityHash {
    std::size_t operator()(const entity& entity) const {
        return std::hash<std::size_t>{}(static_cast<std::size_t>(entity));
    }
};

class Registry {
    public :

        template <class Component>
        sparse_array <Component>& register_component() {
            auto type = std::type_index(typeid(Component));
            if (_components_arrays.find(type) != _components_arrays.end()) {
                throw std::runtime_error("Component already registered");
            }
            auto& array = _components_arrays[type];
            array = std::make_any<sparse_array<Component>>();
            _cleanup_functions.push_back([](Registry& reg, entity const& e) {
                reg.get_components<Component>().erase(e);
            });
            return std::any_cast<sparse_array<Component>&>(array);
        };
        template <class Component>
        sparse_array < Component >& get_components() {
            auto type = std::type_index(typeid(Component));
            if (_components_arrays.find(type) == _components_arrays.end()) {
                throw std::runtime_error("Component not registered");
            }
            return std::any_cast<sparse_array<Component>&>(_components_arrays[type]);
        };
        template <class Component >
        sparse_array < Component > const & get_components() const {
            auto type = std::type_index(typeid(Component));
            if (_components_arrays.find(type) == _components_arrays.end()) {
                throw std::runtime_error("Component not registered");
            }
            return std::any_cast<sparse_array<Component> const &>(_components_arrays.at(type));
        };
        entity spawn_entity() {
            static size_t next_id = 0;
            entity e(next_id++);
            std::cout << "Spawn entity " << e << std::endl;
            return e;
        };
        entity entity_from_index ( std :: size_t idx ) {
            return entity(idx);
        };
        void kill_entity ( entity const & e ) {
            for (auto &erasator : _cleanup_functions) {
                erasator(*this, e);
            }
        };
        template <typename Component >
        typename sparse_array < Component >:: reference_type add_component ( entity const & to,Component && c ) {
            auto & array = get_components < Component >() ;
            auto &count = array.insert_at( static_cast < std :: size_t >( to ) , std :: move ( c ) ) ;
            std::cout << "Added component to entity " << to << std::endl;
            return count;
        };
        template <typename Component , typename ... Params >
        typename sparse_array < Component >:: reference_type emplace_component ( entity const & to, Params &&... p ) {
            auto & array = get_components < Component >() ;
            return array.emplace_at( static_cast < std :: size_t >( to ) , std :: forward < Params >( p )... ) ;
        };
        template <typename Component >
        void remove_component ( entity const & from ) {
            auto & array = get_components < Component >() ;
            array.erase( static_cast < std :: size_t >( from ) ) ;
        };

        template <class... Component, typename Function>
        void add_system(Function&& function) {
            _systems.push_back([function = std::forward<Function>(function)](Registry &reg) {
                function(reg, reg.get_components<Component>()...);
            });
        }

        void run_systems() {
            for (auto& system : _systems) {
                system(*this);
            }
        }
    private :
        std::unordered_map<std::type_index, std::any> _components_arrays;
        std::vector<std::function<void(Registry&, entity const&)>> _cleanup_functions;
        std::vector<std::function<void(Registry &reg)>> _systems;
};