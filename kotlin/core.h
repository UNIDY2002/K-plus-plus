#ifndef KOTLIN_CORE_H
#define KOTLIN_CORE_H

#include <iostream>
#include <string>

// lambda

#define L0(func) [](){func}
#define L1(arg, func) [](arg){func}
#define IT(func) [](auto &it){func}
#define L2(arg0, arg1, func) [](arg0, arg1){func}

#define RL0(exp) [](){return exp;}
#define RL1(arg, exp) [](arg){return exp;}
#define RIT(exp) [](auto &it){return exp;}
#define RL2(arg0, arg1, exp) [](arg0, arg1){return exp;}


namespace kt {

    // types

    typedef int Int;
    typedef double Double;
    typedef float Float;
    typedef long long Long;
    typedef short Short;
    typedef char Char;
    typedef std::string String;
    typedef bool Boolean;

    class Any {
    public:
        void run(void block(Any &)) { block(*this); }

        Any &also(void block(Any &)) {
            block(*this);
            return *this;
        }

        virtual String toString() const { return "Any"; }

        friend std::ostream &operator<<(std::ostream &out, const Any &any) {
            std::cout << any.toString();
            return out;
        }
    };

    class Foo : public Any {
    public:
        String toString() const override { return "Foo"; }
    };

    class Nothing {
    public:
        Nothing() = delete;
    };

    String kToString(Int value) { return std::to_string(value); }

    String kToString(Long value) { return std::to_string(value); }

    String kToString(Double value) { return std::to_string(value); }

    String kToString(Float value) { return std::to_string(value); }

    String kToString(Short value) { return std::to_string(value); }

    String kToString(Boolean value) { return value ? "true" : "false"; }

    String kToString(String s) { return s; }

    String kToString(const char *s) { return String(s); }

    String kToString(Char value) { return String(1, value); }

    template<typename T>
    String kToString(T &any) { return any.toString(); }

    // console

    template<typename T>
    void println(const T &o) {
        std::cout << kToString(o) << std::endl;
    }

    void println() {
        std::cout << std::endl;
    }

    template<typename T>
    void print(const T &o) {
        std::cout << kToString(o);
    }

    String readLine() {
        String input;
        std::cin >> input;
        return input;
    }

    // loops

    void repeat(Int t, void block(Int &)) {
        for (Int i = 0; i < t; ++i) block(i);
    }

    // To-do's

    class NotImplementedError : std::exception {
        const char *what() const noexcept override {
            return "An operation is not implemented.";
        }
    };

    Nothing &TODO() {
        throw NotImplementedError();
    }
}

#endif
