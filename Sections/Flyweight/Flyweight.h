#include <memory>
#include <set>

// Use singleton instead of static data members
// because static data isn't inherited, it's
// shared. This breaks encapsulation.
template <typename T>
class Singleton {
protected:
    Singleton() = default;
public:
    // Declaring deleted methods public results in better error messages.
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    template <typename... Args>
    static T& get_instance(Args... args) { // Accessible without creating instance.
        // Instantiated once, persists until program termination.
        static T instance {std::forward(args)...};
        return instance;
    }
};

template <typename T>
class FlyweightBase : public Singleton<FlyweightBase<T>> { // CRTP.
    // Needs to be a friend to access constructor.
    friend class Singleton<FlyweightBase<T>>;

    // Use smart pointers for polymorphism.
    std::set<std::shared_ptr<T>> data;

    FlyweightBase() = default;
public:
    // Needs to be overloaded to prevent compile-time template error.
    static FlyweightBase<T>& get_instance() {
        return Singleton<FlyweightBase<T>>::get_instance();
    }

    const auto& get_data() const {
        return data;
    }

    // Inserts data in the set if it's unique, regardless it'll return the iterator.
    // Universal reference supports l/r-values.
    static auto get(T &&arg) {
        auto& data_set {get_instance().data};
        auto arg_ptr {std::make_shared<T>(std::forward<T>(arg))};
        auto pair = data_set.insert(arg_ptr);
        return pair.first;
    }
};

// Can't use inheritance as that requires base class constructor.
// Use facade pattern to simplify working with FlyweightBase.
template <typename T>
class Flyweight {
    FlyweightBase<T>& base;
    decltype(base.get_data().begin()) iterator;
public:
    Flyweight(T&& arg)
        : base{FlyweightBase<T>::get_instance()},
          iterator{base.get(std::forward<T>(arg))} {}

    operator T() const {
        return get();
    }

    static size_t unique_count() {
        return FlyweightBase<T>::get_instance().get_data().size();
    };

    const T& get() const {
        return **iterator;
    }
    void set(T&& arg) {
        iterator = base.get(std::forward<T>(arg));
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Flyweight<T> &obj) {
    os << obj.get();
    return os;
}