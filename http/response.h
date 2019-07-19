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
         * @tparam bytebuf_t the byte container type
         * @tparam map_t the map type used to store the headers
         * @see Request
         */
        template<typename bytebuf_t, template<typename, typename> typename map_t>
        class Response : public Transferable<bytebuf_t>
        {
        public:
            virtual ~Response() = default;

            virtual void setStatus(ResponseStatus status) = 0;
            virtual void setHttpVersion(HttpVersion version) = 0;
            virtual void addHeader(bytebuf_t const &key, bytebuf_t const &value) = 0;
            virtual void setHeaders(map_t<bytebuf_t, bytebuf_t> const &headers) = 0;
            virtual void setBody(bytebuf_t const &body, ResponseContentType type = ResponseContentType::TXT) = 0;

            virtual ResponseStatus status() const = 0;
            virtual bytebuf_t body() const = 0;
            virtual HttpVersion httpVersion() const = 0;
            virtual map_t<bytebuf_t, bytebuf_t> headers() const = 0;
            virtual bytebuf_t header(bytebuf_t const &http_header) const = 0;
        };
    }
}