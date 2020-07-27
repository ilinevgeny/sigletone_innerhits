#include <iostream>
//#include <type_traits>
class AbstractEditor
{
    virtual std::string set_tabs() = 0;
};

template<typename T>
class BaseEditor: public AbstractEditor
{
protected:
    //BaseEditor(const BaseEditor&) = delete;
    BaseEditor& operator=(const BaseEditor&) = delete;
    virtual ~BaseEditor() = default;

public:
    static T& get_instance(std::string& uuid) noexcept(std::is_nothrow_constructible<T>::value)
    {
        static T instance;
        instance.init(uuid);
        return instance;
    }

    void setup_form()
    {
        std::cout << "CALL setup_form() BASE METHOD \n";
        std::cout << "Create a base form with common controls \n";
        std::cout << this->set_tabs();
    }

    virtual std::string set_tabs() { return std::string(); };
    void init(std::string uuid)
    {
        std::cout << "uuid is " << uuid << std::endl;
        std::cout << "CALL TO DB CONNECTION " << std::endl;
    };
};

class SetsEditor: public BaseEditor<SetsEditor>
{
    //friend class BaseEditor<SetsEditor>;
public:
    std::string name;
    std::string set_tabs() override
    {
        std::cout << "CALL set_tabs() OF SetsEditor METHOD\n\n\n";
        return this->name;
    };
};

class ConfigEditor : public BaseEditor<ConfigEditor>
{
public:

    std::string set_tabs() override
    {
        std::cout << "CALL set_tabs() OF ConfigEditor METHOD\n";
        return std::string();
    };
};

class EditorFactory
{
public:
    EditorFactory(int type) : typeEditor(type){};
    int typeEditor;
    void setupForm()
    {
        if(typeEditor == 1)
        {
            std::string str = "00000000-0000-0000-0000-000000001000";
            auto editor = static_cast<SetsEditor&>(SetsEditor::get_instance(str));
            editor.setup_form();
        }
        else if(typeEditor == 2)
        {
            std::string str = "00000000-0000-0000-0000-000000001001";
            auto editor = static_cast<ConfigEditor&>(ConfigEditor::get_instance(str));
            editor.setup_form();
        }
    }
};

int main()
{
    int type = 1;
    //std::cin >> type;
    EditorFactory editor(type);
    editor.setupForm();
    return 0;
}
