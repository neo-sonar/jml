/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 lua_juce_core
    vendor:             neo-sonar
    version:            0.1.0
    name:               Lua bindings for juce_core
    description:        Lua/Sol2 bindings for juce_core
    dependencies:       juce_core
    website:            http://github.com/neo-sonar/jml
    license:            BSL-1.0
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_LUA_JUCE_CORE
    #define USE_LUA_JUCE_CORE
#endif

#include <juce_core/juce_core.h>
#include <sol/sol.hpp>

#define LUA_JUCE_WRAP(x) sol::wrap<decltype(x), x>     // NOLINT
#define LUA_JUCE_C_CALL(x) sol::c_call<decltype(x), x> // NOLINT

namespace juce {

namespace lua_detail {

JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wzero-as-null-pointer-constant")

template<typename C>
struct has_toString
{
private:
    template<typename T>
    static constexpr auto check(T*) -> typename std::is_same<decltype(std::declval<T>().toString()), juce::String>::type;

    template<typename>
    static constexpr auto check(...) -> std::false_type;

    using type = decltype(check<C>(0));

public:
    static constexpr bool value = type::value;
};

JUCE_END_IGNORE_WARNINGS_GCC_LIKE

} // namespace lua_detail

template<typename T>
auto to_string(T const& val) -> std::enable_if_t<lua_detail::has_toString<T>::value, std::string>
{
    return val.toString().toStdString();
}

template<typename T>
auto to_string(T const& val) -> decltype(val.toStdString())
{
    return val.toStdString();
}
} // namespace juce

template<>
struct sol::is_container<juce::MemoryBlock> : std::false_type
{};

template<>
struct sol::is_container<juce::String> : std::false_type
{};

template<>
struct sol::is_container<juce::StringArray> : std::false_type
{};

template<typename T>
struct sol::is_container<juce::Array<T>> : std::false_type
{};

namespace lua_juce {
auto juce_Array(sol::table& state) -> void;
auto juce_File(sol::table& state) -> void;
auto juce_BigInteger(sol::table& state) -> void;
auto juce_Int(sol::table& state) -> void;
auto juce_MathConstants(sol::table& state) -> void;
auto juce_NormalisableRange(sol::table& state) -> void;
auto juce_Random(sol::table& state) -> void;
auto juce_Range(sol::table& state) -> void;
auto juce_StatisticsAccumulator(sol::table& state) -> void;
auto juce_MemoryBlock(sol::table& state) -> void;
auto juce_Result(sol::table& state) -> void;
auto juce_Uuid(sol::table& state) -> void;
auto juce_IPAddress(sol::table& state) -> void;
auto juce_InputStream(sol::table& state) -> void;
auto juce_MemoryInputStream(sol::table& state) -> void;
auto juce_MemoryOutputStream(sol::table& state) -> void;
auto juce_OutputStream(sol::table& state) -> void;
auto juce_String(sol::table& state) -> void;
auto juce_StringArray(sol::table& state) -> void;
auto juce_PerformanceCounter(sol::table& state) -> void;
auto juce_RelativeTime(sol::table& state) -> void;
auto juce_Time(sol::table& state) -> void;

template<typename T>
auto juce_ArrayImpl(sol::table& state, char const* name) -> void
{
    auto noOperators                           = sol::automagic_enrollments{};
    noOperators.less_than_operator             = false;
    noOperators.less_than_or_equal_to_operator = false;
    noOperators.equal_to_operator              = false;

    auto array = state.new_usertype<juce::Array<T>>(name, noOperators);

    array["clear"]                    = LUA_JUCE_C_CALL(&juce::Array<T>::clear);
    array["clearQuick"]               = LUA_JUCE_C_CALL(&juce::Array<T>::clearQuick);
    array["fill"]                     = LUA_JUCE_C_CALL(&juce::Array<T>::fill);
    array["size"]                     = LUA_JUCE_C_CALL(&juce::Array<T>::size);
    array["isEmpty"]                  = LUA_JUCE_C_CALL(&juce::Array<T>::isEmpty);
    array["getUnchecked"]             = LUA_JUCE_C_CALL(&juce::Array<T>::getUnchecked);
    array["getFirst"]                 = LUA_JUCE_C_CALL(&juce::Array<T>::getFirst);
    array["getLast"]                  = LUA_JUCE_C_CALL(&juce::Array<T>::getLast);
    array["insert"]                   = LUA_JUCE_C_CALL(&juce::Array<T>::insert);
    array["insertMultiple"]           = LUA_JUCE_C_CALL(&juce::Array<T>::insertMultiple);
    array["set"]                      = LUA_JUCE_C_CALL(&juce::Array<T>::set);
    array["setUnchecked"]             = LUA_JUCE_C_CALL(&juce::Array<T>::setUnchecked);
    array["resize"]                   = LUA_JUCE_C_CALL(&juce::Array<T>::resize);
    array["removeAndReturn"]          = LUA_JUCE_C_CALL(&juce::Array<T>::removeAndReturn);
    array["removeRange"]              = LUA_JUCE_C_CALL(&juce::Array<T>::removeRange);
    array["removeLast"]               = LUA_JUCE_C_CALL(&juce::Array<T>::removeLast);
    array["swap"]                     = LUA_JUCE_C_CALL(&juce::Array<T>::swap);
    array["move"]                     = LUA_JUCE_C_CALL(&juce::Array<T>::move);
    array["minimiseStorageOverheads"] = LUA_JUCE_C_CALL(&juce::Array<T>::minimiseStorageOverheads);
    array["ensureStorageAllocated"]   = LUA_JUCE_C_CALL(&juce::Array<T>::ensureStorageAllocated);
    array["add"]                      = [](juce::Array<T>* a, T const& t) { a->add(t); };

    // array["indexOf"]                  = &juce::Array<T>::indexOf;
    // array["contains"]                 = &juce::Array<T>::contains;
    // array["addIfNotAlreadyThere"]     = &juce::Array<T>::addIfNotAlreadyThere;
    // array["swapWith"]                 = &juce::Array<T>::swapWith;
    // array["addSorted"]                = &juce::Array<T>::addSorted;
    // array["addUsingDefaultSort"]      = &juce::Array<T>::addUsingDefaultSort;
    // array["indexOfSorted"]            = &juce::Array<T>::indexOfSorted;
    // array["removeFirstMatchingValue"] = &juce::Array<T>::removeFirstMatchingValue;
    // array["removeAllInstancesOf"]     = &juce::Array<T>::removeAllInstancesOf;
    // array["removeIf"]                 = &juce::Array<T>::removeIf;
    // array["removeValuesIn"]           = &juce::Array<T>::removeValuesIn;
    // array["removeValuesNotIn"]        = &juce::Array<T>::removeValuesNotIn;

    // TODO(tobi)
    // getReference
    // getRawDataPointer
    // begin
    // end
    // data
    // add
    // insertArray
    // addArray
    // addNullTerminatedArray
    // remove
    // sort
    // getLock
}

struct SolObjectSet final : juce::ReferenceCountedObject
{
    using Ptr = juce::ReferenceCountedObjectPtr<SolObjectSet>;

    SolObjectSet()           = default;
    ~SolObjectSet() override = default;

    auto contains(sol::object obj) -> bool { return _objects.count(obj) == 1U; }

    auto add(sol::object obj) -> void
    {
        if (_objects.count(obj) == 1U) { return; }
        _objects.insert(std::move(obj));
    }

    auto remove(sol::object obj) -> void
    {
        jassert(_objects.count(obj) == 1U);
        _objects.erase(obj);
    }

private:
    std::unordered_set<sol::object, sol::reference_hash> _objects;
};

inline auto getOrCreateSolObjectSet(juce::NamedValueSet& properties) -> SolObjectSet&
{
    if (properties.contains("lua-objects")) {
        auto const& v = properties["lua-objects"];
        auto* objects = dynamic_cast<SolObjectSet*>(v.getObject());
        jassert(objects != nullptr);
        return *objects;
    }

    auto* objects = new SolObjectSet{};
    properties.set("lua-objects", objects);
    return *objects;
}

} // namespace lua_juce
