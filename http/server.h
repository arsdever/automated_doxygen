#pragma once

#include <http/request.h>
#include <http/response.h>
#include <http/authenticator.h>

namespace ad
{
    namespace http
    {
        template <typename BYTEBUF_TYPE, typename MAP_TYPE>
        class Server
        {
        public:
            typedef BYTEBUF_TYPE bytebuf_t;
            typedef MAP_TYPE map_t;
            typedef Server<bytebuf_t, map_t> root_t;
            typedef ad::http::Request<bytebuf_t, map_t> request_t;
            typedef ad::http::Response<bytebuf_t, map_t> response_t;
            typedef ad::http::Authenticator<bytebuf_t> authenticator_t;
            typedef void (*handler_t) (request_t&, response_t&);

        public:
            virtual ~Server() = default;

            virtual void begin(unsigned short port) = 0;

            virtual void _get(bytebuf_t const &endpoint, handler_t handler) = 0;
            virtual void _head(bytebuf_t const &endpoint, handler_t handler) = 0;
            virtual void _post(bytebuf_t const &endpoint, handler_t handler) = 0;
            virtual void _put(bytebuf_t const &endpoint, handler_t handler) = 0;
            virtual void _delete(bytebuf_t const &endpoint, handler_t handler) = 0;
            virtual void _connect(bytebuf_t const &endpoint, handler_t handler) = 0;
            virtual void _options(bytebuf_t const &endpoint, handler_t handler) = 0;
            virtual void _trace(bytebuf_t const &endpoint, handler_t handler) = 0;
            virtual void _patch(bytebuf_t const &endpoint, handler_t handler) = 0;
            virtual void method(bytebuf_t const &method, bytebuf_t const &endpoint, handler_t handler) = 0;

            virtual void cd(bytebuf_t const &dir) = 0;
            virtual bytebuf_t currentDir() const = 0;
            virtual bytebuf_t pathTo(bytebuf_t const &path) const = 0;

            virtual void setAuthenticator(authenticator_t *authenticator) = 0;
            virtual authenticator_t* authenticator() const = 0;
        };
    }
}