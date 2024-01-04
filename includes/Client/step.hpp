#include <iostream>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <vector>
#include <functional>
#include <any>
#include <exception>
#include <optional>
#include <tuple>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

/**
 * @file step.hpp
 * @brief Entity Component System (ECS) architecture and utilities for game development.
 *
 * This file provides the necessary classes and structures to implement an ECS architecture in a game.
 * It includes the definition of components like Position, Velocity, Controllable, Drawable, BulletTag, 
 * EnemyTag, BossTag, Timer, ExplosionTag, and Song. It also defines the MusicManager class for handling
 * music resources, an entity class as a unique identifier for entities, a sparse_array template for component
 * storage, and a Registry class for managing entities and their components. The file uses SFML for rendering 
 * and multimedia handling.
 *
 * @version 1.0
 * @date 2023-12-25
 * @author Andrea Mancion
 * 
 * @note This file is part of the Epitech Project, B-CPP-500-REN-5-2-rtype-andrea.mancion.
 */

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

struct Drawable {
    sf::Sprite sprites;
};

struct BulletTag {
    bool isBullet;

    BulletTag(bool isBullet) : isBullet(isBullet) {}
};

struct EnemyTag {
    bool isEnemy;

    EnemyTag(bool isEnemy) : isEnemy(isEnemy) {}
};

struct BossTag {
    bool isBoss;

    BossTag(bool isBoss) : isBoss(isBoss) {}
};

struct BossUltimateTag {
    bool isBoss;

    BossUltimateTag(bool isBoss) : isBoss(isBoss) {}
};

struct Timer {
    float elapsedTime = 0.0f;
    float shootInterval;

    Timer(float interval) : shootInterval(interval) {}
};

struct ExplosionTag {
    bool isExplosion;

    ExplosionTag(bool isExplosion) : isExplosion(isExplosion) {}
};

struct Song {
    int musicID;
    bool isEnemy;
    bool shouldPlay;
    bool isPlaying;

    Song(int id, bool EnemySong, bool ShouldPlay, bool IsPlaying) : isEnemy(EnemySong), musicID(id), shouldPlay(ShouldPlay), isPlaying(IsPlaying) {}
};

/**
 * @class MusicManager
 * @brief Manages music resources within the game.
 *
 * The MusicManager class is responsible for loading, storing, and providing access to music tracks.
 * It assigns a unique ID to each loaded track, allowing for efficient management and retrieval of
 * music resources.
 */

class MusicManager {
    private:
        int nextID = 0;
        std::unordered_map<int, std::unique_ptr<sf::Music>> _songs;
    public:
        int loadMusic(const std::string &filename) {
            auto music = std::make_unique<sf::Music>();
            if (music->openFromFile(filename)) {
                int id = nextID++;
                _songs[id] = std::move(music);
                return id;
            }
            return -1;
        }

        sf::Music* getMusic(int id) {
            auto it = _songs.find(id);
            if (it != _songs.end()) {
                return it->second.get();
            }
            return nullptr;
        }
};

class entity {
    friend class Registry;

    private:
        size_t x;
    public:
        explicit entity(size_t x) : x(x) {}
        operator std::size_t() const { return x; }
};

/**
 * @brief A template class that provides a space-efficient array with optional elements.
 *
 * @tparam Component The type of component to store in the array.
 */

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