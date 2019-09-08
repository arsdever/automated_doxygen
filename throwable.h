#pragma once

namespace ad
{
    template <typename STRING_TYPE>
    class Throwable
    {
    public:
        typedef STRING_TYPE string_t;

    public:
        virtual ~Throwable() = default;
        virtual string_t what() const = 0;
        virtual Throwable const* cause() const = 0;
        virtual string_t toString() const = 0;
    };
}