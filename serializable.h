#pragma once
namespace ad
{
	class ByteBuf;

	/**
	 * \brief This interface is used to serialize the objects.
	 * 
	 * After serialization the objects can be deserialized from the data if they implement the interface **Deserializable**
	 * \see Deserializable
	 */
	template <typename BYTE_ARRAY_TYPE>
	class Serializable
	{
	public:
		/**
		 * \brief The destructor.
		 */
		virtual ~Serializable() = default;

		/**
		 * \brief This function serializes the object.
		 * \return serialized object in ByteBuf
		 * \see ByteBuf
		 */
		virtual BYTE_ARRAY_TYPE serialize() const = 0;
	};
}
