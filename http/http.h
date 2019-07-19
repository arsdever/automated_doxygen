#pragma once

namespace ad
{
    /**
     * @brief This namespace contains useful tools for http protocol manipulation.
     */
    namespace http
    {
        /**
         * @brief This is the enum of standard response reason-phrases associated with their status codes.
         * 
         * @see [**HTTP/1.1** response documentation](https://www.w3.org/Protocols/rfc2616/rfc2616-sec6.html)
         * @see reasonPhrase(ResponseStatus)
         */
        enum class ResponseStatus
        {
            Continue = 100,
            SwitchingProtocols = 101,
            Ok = 200,
            Created = 201,
            Accepted = 202,
            NonAuthoritativeInformation = 203,
            NoContent = 204,
            ResetContent = 205,
            PartialContent = 206,
            MultipleChoices = 300,
            MovedPermanently = 301,
            Found = 302,
            SeeOther = 303,
            NotModified = 304,
            UseProxy = 305,
            TemporaryRedirect = 306,
            BadRequest = 400,
            Unauthorized = 401,
            PaymentRequired = 402,
            Forbidden = 403,
            NotFound = 404,
            MethodNotAllowed = 405,
            NotAcceptible = 406,
            ProxyAuthenticationRequired = 407,
            RequestTimeout = 408,
            Conflict = 409,
            Gone = 410,
            LengthRequired = 411,
            PreconditionFailed = 412,
            RequestEntityTooLarge = 413,
            RequestURITooLarge = 414,
            UnsupportedMediaType = 415,
            RequestedRangeNotSatisfiable = 416,
            ExpectationFailed = 417,
            InternalServerError = 500,
            NotImplemented = 501,
            BadGateway = 502,
            ServiceUnavailable = 503,
            GatewayTimeout = 504,
            HTTPVersionNotSupported = 505
        };

        /**
         * @brief This is the enum of standard HTTP request methods.
         * 
         * @see [**HTTP/1.1** request documentation](https://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html#sec5)
         */
        enum class RequestMethod
        {
            Invalid = 0,
            Get,
            Head,
            Post,
            Put,
            Delete,
            Connect,
            Options,
            Trace,
            Patch
        };

        /**
         * @brief This is the enum of standard HTTP versions.
         * 
         * @see [**HTTP/1.1** HTTP version documentation](https://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html#sec5)
         */
        enum class HttpVersion
        {
            Unsupported = 0,
            Http,
            Http1_1
        };

        /**
         * @brief This is the enum of "Content-Type" header's standard values.
         * 
         * @see [**HTTP/1.1** Content-Type documentation](https://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.17)
         * @see fromContentType
         */
        enum class ContentType
        {
            AAC,
            ABW,
            ARC,
            AVI,
            AZW,
            BIN,
            BMP,
            BZ,
            BZ2,
            CSH,
            CSS,
            CSV,
            DOC,
            DOCX,
            EOT,
            EPUB,
            GIF,
            HTM,
            HTML = HTM,
            ICO,
            ICS,
            JAR,
            JPEG,
            JPG = JPEG,
            JS,
            JSON,
            JSONLD,
            MID,
            MIDI,
            MJS,
            MP3,
            MPEG,
            MPKG,
            ODP,
            ODS,
            ODT,
            OGA,
            OGV,
            OGX,
            OTF,
            PNG,
            PDF,
            PPT,
            PPTX,
            RAR,
            RTF,
            SH,
            SVG,
            SWF,
            TAR,
            TIF,
            TIFF = TIF,
            TS,
            TTF,
            TXT,
            VSD,
            WAV,
            WEBA,
            WEBM,
            WEBP,
            WOFF,
            WOFF2,
            XHTML,
            XLS,
            XLSX,
            ApplicationXML,
            TextXML,
            XUL,
            ZIP,
            Video3GP,
            Audio3GP,
            Video3G2,
            Audio3G2,
            Archive7Z
        };
            
        /**
         * @brief This function returns string literal of request method.
         * 
         * @param method the request method
         * @return string representation of request method
         * @see RequestMethod
         */
        inline constexpr char const* methodVerbose(RequestMethod method)
        { 
            switch(method)
            {
                case RequestMethod::Invalid: return "INVALID";
                case RequestMethod::Get: return "GET";
                case RequestMethod::Head: return "HEAD";
                case RequestMethod::Post: return "POST";
                case RequestMethod::Put: return "PUT";
                case RequestMethod::Delete: return "DELETE";
                case RequestMethod::Connect: return "CONNECT";
                case RequestMethod::Options: return "OPTIONS";
                case RequestMethod::Trace: return "TRACE";
                case RequestMethod::Patch: return "PATCH";
                default: return "";
            }
        }

        /**
         * @brief This function returns string literal of requested HTTP version.
         * 
         * @param version the HTTP version
         * @return string representation of requested HTTP version
         * @see HttpVersion
         */
        inline constexpr char const* httpVersionVerbose(HttpVersion version)
        {
            switch(version)
            {
                case HttpVersion::Http: return "HTTP";
                case HttpVersion::Http1_1: return "HTTP/1.1";
                default: return "UNKNOWN";
            }
        }

        /**
         * @brief This function returns string literal of requested content type.
         * 
         * @param type the content type
         * @return string representation of requested content type
         * @see ContentType
         */
        inline constexpr char const* contentTypeVerbose(ContentType type)
        {
            switch(type)
            {
                case ContentType::AAC: return "audio/aac";
                case ContentType::ABW: return "application/x-abiword";
                case ContentType::ARC: return "application/x-freearc";
                case ContentType::AVI: return "video/x-msvideo";
                case ContentType::AZW: return "application/vnd.amazon.ebook";
                case ContentType::BIN: return "application/octet-stream";
                case ContentType::BMP: return "image/bmp";
                case ContentType::BZ: return "application/x-bzip";
                case ContentType::BZ2: return "application/x-bzip2";
                case ContentType::CSH: return "application/x-csh";
                case ContentType::CSS: return "text/css";
                case ContentType::CSV: return "text/csv";
                case ContentType::DOC: return "application/msword";
                case ContentType::DOCX: return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
                case ContentType::EOT: return "application/vnd.ms-fontobject";
                case ContentType::EPUB: return "application/epub+zip";
                case ContentType::GIF: return "image/gif";
                case ContentType::HTML: return "text/html";
                case ContentType::ICO: return "image/vnd.microsoft.icon";
                case ContentType::ICS: return "text/calendar";
                case ContentType::JAR: return "application/java-archive";
                case ContentType::JPEG: return "image/jpeg";
                case ContentType::JS: return "text/javascript";
                case ContentType::JSON: return "application/json";
                case ContentType::JSONLD: return "application/ld+json";
                case ContentType::MID: return "audio/midi";
                case ContentType::MIDI: return "audio/x-midi";
                case ContentType::MJS: return "text/javascript";
                case ContentType::MP3: return "audio/mpeg";
                case ContentType::MPEG: return "video/mpeg";
                case ContentType::MPKG: return "application/vnd.apple.installer+xml";
                case ContentType::ODP: return "application/vnd.oasis.opendocument.presentation";
                case ContentType::ODS: return "application/vnd.oasis.opendocument.spreadsheet";
                case ContentType::ODT: return "application/vnd.oasis.opendocument.text";
                case ContentType::OGA: return "audio/ogg";
                case ContentType::OGV: return "video/ogg";
                case ContentType::OGX: return "application/ogg";
                case ContentType::OTF: return "font/otf";
                case ContentType::PNG: return "image/png";
                case ContentType::PDF: return "application/pdf";
                case ContentType::PPT: return "application/vnd.ms-powerpoint";
                case ContentType::PPTX: return "application/vnd.openxmlformats-officedocument.presentationml.presentation";
                case ContentType::RAR: return "application/x-rar-compressed";
                case ContentType::RTF: return "application/rtf";
                case ContentType::SH: return "application/x-sh";
                case ContentType::SVG: return "image/svg+xml";
                case ContentType::SWF: return "application/x-shockwave-flash";
                case ContentType::TAR: return "application/x-tar";
                case ContentType::TIFF: return "image/tiff";
                case ContentType::TS: return "video/mp2t";
                case ContentType::TTF: return "font/ttf";
                case ContentType::TXT: return "text/plain";
                case ContentType::VSD: return "application/vnd.visio";
                case ContentType::WAV: return "audio/wav";
                case ContentType::WEBA: return "audio/webm";
                case ContentType::WEBM: return "video/webm";
                case ContentType::WEBP: return "image/webp";
                case ContentType::WOFF: return "font/woff";
                case ContentType::WOFF2: return "font/woff2";
                case ContentType::XHTML: return "application/xhtml+xml";
                case ContentType::XLS: return "application/vnd.ms-excel";
                case ContentType::XLSX: return "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
                case ContentType::ApplicationXML: return "application/xml";
                case ContentType::TextXML: return "text/xml";
                case ContentType::XUL: return "application/vnd.mozilla.xul+xml";
                case ContentType::ZIP: return "application/zip";
                case ContentType::Video3GP: return "video/3gpp";
                case ContentType::Audio3GP: return "audio/3gpp";
                case ContentType::Video3G2: return "video/3gpp2";
                case ContentType::Audio3G2: return "audio/3gpp2";
                case ContentType::Archive7Z: return "application/x-7z-compressed";
                default: return "";
            }
        }

        /**
         * @brief This function returns the standard reason-phrase of status code.
         * 
         * @param code the status code
         * @return the standard reason-phrase of status code
         * @see ResponseStatus
         */
        inline constexpr char const* reasonPhraseVerbose(ResponseStatus code)
        {
            switch(code)
            {
                case ResponseStatus::Continue: return "Continue";
                case ResponseStatus::SwitchingProtocols: return "Switching Protocols";
                case ResponseStatus::Ok: return "OK";
                case ResponseStatus::Created: return "Created";
                case ResponseStatus::Accepted: return "Accepted";
                case ResponseStatus::NonAuthoritativeInformation: return "Non-Authoritative Information";
                case ResponseStatus::NoContent: return "No Content";
                case ResponseStatus::ResetContent: return "Reset Content";
                case ResponseStatus::PartialContent: return "Partial Content";
                case ResponseStatus::MultipleChoices: return "Multiple Choices";
                case ResponseStatus::MovedPermanently: return "Moved Permanently";
                case ResponseStatus::Found: return "Found";
                case ResponseStatus::SeeOther: return "See Other";
                case ResponseStatus::NotModified: return "Not Modified";
                case ResponseStatus::UseProxy: return "Use Proxy";
                case ResponseStatus::TemporaryRedirect: return "Temporary Redirect";
                case ResponseStatus::BadRequest: return "Bad Request";
                case ResponseStatus::Unauthorized: return "Unauthorized";
                case ResponseStatus::PaymentRequired: return "Payment Required";
                case ResponseStatus::Forbidden: return "Forbidden";
                case ResponseStatus::NotFound: return "Not Found";
                case ResponseStatus::MethodNotAllowed: return "Method Not Allowed";
                case ResponseStatus::NotAcceptible: return "Not Acceptable";
                case ResponseStatus::ProxyAuthenticationRequired: return "Proxy Authentication Required";
                case ResponseStatus::RequestTimeout: return "Request Time-out";
                case ResponseStatus::Conflict: return "Conflict";
                case ResponseStatus::Gone: return "Gone";
                case ResponseStatus::LengthRequired: return "Length Required";
                case ResponseStatus::PreconditionFailed: return "Precondition Failed";
                case ResponseStatus::RequestEntityTooLarge: return "Request Entity Too Large";
                case ResponseStatus::RequestURITooLarge: return "Request-URI Too Large";
                case ResponseStatus::UnsupportedMediaType: return "Unsupported Media Type";
                case ResponseStatus::RequestedRangeNotSatisfiable: return "Requested range not satisfiable";
                case ResponseStatus::ExpectationFailed: return "Expectation Failed";
                case ResponseStatus::InternalServerError: return "Internal Server Error";
                case ResponseStatus::NotImplemented: return "Not Implemented";
                case ResponseStatus::BadGateway: return "Bad Gateway";
                case ResponseStatus::ServiceUnavailable: return "Service Unavailable";
                case ResponseStatus::GatewayTimeout: return "Gateway Time-out";
                case ResponseStatus::HTTPVersionNotSupported: return "HTTP Version not supported";
                default: return "";
            }
        }
    }
}