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
};

void instantiate_MyClass() {
    auto object = MyClass("name", "title", 1);

    object.Print();
}
