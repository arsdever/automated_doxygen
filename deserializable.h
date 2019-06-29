#pragma once
namespace ad
{
	class ByteBuf;

	/**
	 * \brief This interface is used to deserialize the objects.
	 * 
	 * Objects can be deserialized from the data serialized using the interface Serializable.
	 * It also is possible to deserialize from custom defined data (if such implementation exists).
	 * \see Serializable
	 */
	class Deserializable
	{
	public:
		/**
		 * \brief The destructor.
		 */
		virtual ~Deserializable() = default;

		/**
		 * \brief This function deserializes the object.
		 * \param buf the buffer to get data from
		 * \see ByteBuf
		 */
		virtual void deserialize(ByteBuf const *buf) = 0;

		/**
		 * \brief This function deserializes the object.
		 * \param data the data
		 */
		virtual void deserialize(char const *data) = 0;
	};
}
