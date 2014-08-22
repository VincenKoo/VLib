#ifndef AUTO_REGISTER_CATEGORY_HPP
#define AUTO_REGISTER_CATEGORY_HPP

#include <map>
#include <string>


#define BEGIN_DECLARE_AUTO_REGISTER_CATEGORY(CLASS_NAME) \
class CLASS_NAME \
{ \
public: \
    typedef std::map<std::string, CLASS_NAME*> ClassMap; \
    class Factory \
    { \
    public: \
        static CLASS_NAME* create(const std::string& name) \
        { \
            CLASS_NAME* parser = CLASS_NAME::_map[name]; \
            if (parser != NULL) { \
                parser = parser->_clone(); \
            } \
            return parser; \
        } \
    }; \
    virtual ~CLASS_NAME(void) { } \
protected: \
    CLASS_NAME(void) { } \
    CLASS_NAME(const std::string& name) \
    { \
        _register(name); \
    } \
    virtual CLASS_NAME* _clone(void) = 0; \
    void _register(const std::string& name) \
    { \
        _map[name] = this; \
    } \
    static ClassMap _map; \
private: \


#define END_DECLARE_AUTO_REGISTER_CATEGORY(CLASS_NAME) \
}; \
CLASS_NAME::ClassMap CLASS_NAME::_map;



#define BEGIN_DECLARE_SUB_AUTO_REGISTER_CATEGORY(SUB_CLASS_NAME, BASE_CLASS_NAME) \
class SUB_CLASS_NAME : public BASE_CLASS_NAME \
{ \
    SUB_CLASS_NAME(void) { } \
    SUB_CLASS_NAME(const std::string& name) \
        : BASE_CLASS_NAME(name) \
    { \
    } \
    virtual BASE_CLASS_NAME* _clone(void) \
    { \
        return new SUB_CLASS_NAME(); \
    } \
    static SUB_CLASS_NAME _default_instance;


#define END_DECLARE_SUB_AUTO_REGISTER_CATEGORY(SUB_CLASS_NAME, REFLECTION_NAME) \
}; \
SUB_CLASS_NAME SUB_CLASS_NAME::_default_instance(REFLECTION_NAME);


#endif // AUTO_REGISTER_CATEGORY_HPP
