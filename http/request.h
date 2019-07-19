#pragma once

#include "http.h"
#include "../transferable.h"

namespace ad
{
    namespace http
    {
        /**
         * @brief This is an interface for HTTP request.
         * 
         * @tparam bytebuf_t the byte container type
         * @tparam map_t the map type used to store the headers
         * @see Response
         */
        template<typename bytebuf_t, template<typename, typename> typename map_t>
        class Request : public Transferable<bytebuf_t>
        {
        public:
            /**
             * @brief The destructor.
             * 
            */
            virtual ~Request() = default;

            /**
             * @brief Add a new request header.
             * 
             * @param key the header name
             * @param value the header value
             */
            virtual void addHeader(bytebuf_t const &key, bytebuf_t const &value) = 0;

            /**
             * @brief Set the request headers.
             * 
             * @param headers the new headers
             */
            virtual void setHeaders(map_t<bytebuf_t, bytebuf_t> const &headers) = 0;

            /**
             * @brief Set the request body.
             * 
             * @param body the new body.
             */
            virtual void setBody(bytebuf_t const &body) = 0;

            /**
             * @brief Set the request method.
             * 
             * @param method the request method
             */
            virtual void setMethod(RequestMethod method) = 0;

            /**
             * @brief Set the http version.
             * 
             * @param version the http version
             */
            virtual void setHttpVersion(HttpVersion version) = 0;

            /**
             * @brief Set the request target path.
             * 
             * @param target the target path
             */
            virtual void setTarget(bytebuf_t const &target) = 0;

            /**
             * @brief Get the request header.
             * 
             * @param header the request header
             * @return the requested header's value
             * @see headers
             */
            virtual bytebuf_t header(bytebuf_t const &header) const = 0;

            /**
             * @brief Get the all specified request headers.
             * 
             * @return the request headers map
             * @see header 
             */
            virtual map_t<bytebuf_t, bytebuf_t> headers() const = 0;

            /**
             * @brief Get the request's http version.
             * 
             * @return the http version
             */
            virtual HttpVersion httpVersion() const = 0;

            /**
             * @brief Get the request method.
             * 
             * @return the request method
             */
            virtual RequestMethod method() const = 0;

            /**
             * @brief Get the request target path.
             * 
             * @return the target path
             */
            virtual bytebuf_t target() const = 0;

            /**
             * @brief Get the request body.
             * 
             * @return the request body
             */
            virtual bytebuf_t body() const = 0;
        };
    }
}