#!/bin/python3

import ROOT

ROOT.gInterpreter.Declare("""
class MyClass : public TObject {
public:
    inline MyClass(std::string const &name, std::string const &title, int value)
        : name_{name}, title_{title}, value_{value}
    {
    }

    inline void Print(Option_t *option = "") const override
    {
        std::cout << name_ << "  " << title_ << "  " << value_ << std::endl;
    }

private:
    std::string name_;
    std::string title_;
    int value_;
};""")

obj = ROOT.MyClass(ROOT.std.string("name"), ROOT.std.string("title"), 1)

obj.Print()
