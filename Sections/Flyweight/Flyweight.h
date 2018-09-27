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

    // Inserts data in the set if it's unique, eitherway it'll return the iterator.
    // Universal reference supports l/r-values.
    static auto get(T&& arg) {
        auto& data_set {get_instance().data};
        auto arg_ptr {make_shared<T>(std::forward<T>(arg))};
        auto pair = data_set.insert(arg_ptr);
        return pair.first;
    }
};

// Can't use inheritance as that requires base class constructor.
// Use facade pattern to simplify working with FlyweightBase.
template <typename T>
class Flyweight {
    FlyweightBase<T>& base;
public:
    Flyweight() : base{FlyweightBase<T>::get_instance()} {}

    auto get(T&& arg) {
        return base.get(std::forward<T>(arg));
    }
};