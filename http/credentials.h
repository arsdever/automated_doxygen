#pragma once

namespace ad
{
    namespace http
    {
        /**
         * @brief The existing hashing algorithms enum
         * 
         * TODO: Move to another namespace like ad::crypto
         */
        enum HashAlgorithm
        {
            MD5,
            Blowfish,
            SHA_256,
            SHA_512,
            Other
        };

        /**
         * @brief This interface is used to store a user credentials. It also provides functionality to hash the
         * password. 
         * 
         * @tparam bytebuf_t then byte array type
         */
        template <typename BYTEBUF_TYPE>
        class Credentials
        {
        public:
            typedef BYTEBUF_TYPE bytebuf_t;

        public:
            /**
             * @brief Default destructor.
             */
            virtual ~Credentials() = default;

            /**
             * @brief Set the username.
             * 
             * @param username the username
             */
            virtual void setUsername(bytebuf_t const &username) = 0;
            
            /**
             * @brief Set the password.
             * 
             * @param password the password
             */
            virtual void setPassword(bytebuf_t const &password) = 0;

            /**
             * @brief Set the hashed password
             * 
             * @param hpassword the hashed password
             */
            virtual void setHashedPassword(bytebuf_t const &hpassword) = 0;

            /**
             * @brief Set the salt.
             * 
             * @param salt the salt
             */
            virtual void setSalt(bytebuf_t const &salt) = 0;

            /**
             * @brief Set the hash algorithm.
             * 
             * @param algorithm the algorithm type 
             */
            virtual void setHashAlgorithm(HashAlgorithm algorithm) = 0;

            /**
             * @brief Get the username.
             * 
             * @return the username
             */
            virtual bytebuf_t username() const = 0;

            /**
             * @brief Get the password.
             * 
             * @return the password
             */
            virtual bytebuf_t password() const = 0;

            /**
             * @brief Get the hashed password.
             * 
             * The password was hashed using the salt which can be gotten using @a{salt()} function.
             * @return the hashed password
             * @see salt()
             */
            virtual bytebuf_t hashedPassword() const = 0;

            /**
             * @brief Get the salt of hashing.
             * 
             * @return the salt
             */
            virtual bytebuf_t salt() const = 0;
            
            /**
             * @brief Get the hash algorithm
             * 
             * @return the hash algorithm
             */
            virtual HashAlgorithm hashAlgorithm() const = 0;

            /**
             * @brief Clear the credentials.
             * 
             * Equivalent to setting all the fields to an empty byte array.
             */
            virtual void clear() = 0;
        };
    }
}