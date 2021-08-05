#pragma once

#include "../Objects/Core/Serialization/FArchive.h"

namespace upp::Readers {
    template<class T>
    class NameMappedArchive : public T {
        static_assert(std::is_base_of_v<Objects::FArchive, T>, "T must be a derivative of FArchive");

    public:
        template<class... ArgsT>
        NameMappedArchive(const std::vector<std::string>& NameMap, ArgsT&&... Args) :
            T(std::forward<ArgsT>(Args)...),
            NameMap(NameMap)
        {

        }

        Objects::FArchive& operator>>(Objects::FName& Val) override
        {
            T::operator>>(Val);
            Val.String = &NameMap[Val.Index];

            return *this;
        }

        const std::string& GetName(uint32_t Idx) const
        {
            return NameMap[Idx];
        }

    private:
        const std::vector<std::string>& NameMap;
    };

    template<class T>
    NameMappedArchive(const std::vector<std::string>&, T&&) -> NameMappedArchive<T>;
}