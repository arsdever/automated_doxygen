#pragma once

namespace ad
{
    namespace http
    {
        template <typename BYTEBUF_TYPE>
        class Authenticator
        {
        public:
            typedef BYTEBUF_TYPE bytebuf_t;

        public:
            virtual ~Authenticator() = default;

            virtual bool authenticate(bytebuf_t const &value, bool no_throw = true) const = 0;
            virtual void registerUser(bytebuf_t const &username, bytebuf_t const &password) = 0;
            virtual void unregisterUser(bytebuf_t const &username, bytebuf_t const &password) = 0;
        };
    }    
}