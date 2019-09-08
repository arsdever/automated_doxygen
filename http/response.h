#pragma once

#include "http.h"
#include "../transferable.h"

namespace ad
{
    namespace http
    {
        /**
         * @brief This is an interface for HTTP response.
         * 
         * @tparam BYTEBUF_TYPE the byte container type
         * @tparam MAP_TYPE the map type used to store the headers
         * @see Request
         */
        template<typename BYTEBUF_TYPE, typename MAP_TYPE>
        class Response : public Transferable<BYTEBUF_TYPE>
        {
        public:
            typedef BYTEBUF_TYPE bytebuf_t;
            typedef MAP_TYPE map_t;
            typedef Transferable<bytebuf_t> base_t;

        public:
            virtual ~Response() = default;

            virtual void setStatus(ResponseStatus status) = 0;
            virtual void setHttpVersion(HttpVersion version) = 0;
            virtual void addHeader(bytebuf_t const &key, bytebuf_t const &value) = 0;
            virtual void setHeaders(map_t const &headers) = 0;
            virtual void setBody(bytebuf_t const &body, ContentType type = ContentType::TXT) = 0;

            virtual ResponseStatus status() const = 0;
            virtual bytebuf_t body() const = 0;
            virtual HttpVersion httpVersion() const = 0;
            virtual map_t headers() const = 0;
            virtual bytebuf_t header(bytebuf_t const &http_header) const = 0;
        };
    }
}