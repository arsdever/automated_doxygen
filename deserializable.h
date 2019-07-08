#pragma once
namespace ad
{
	/**
	 * \brief This interface is used to deserialize the objects.
	 * 
	 * Objects can be deserialized from the data serialized using the interface Serializable.
	 * It also is possible to deserialize from custom defined data (if such implementation exists).
	 * \see Serializable
	 */
	template <typename BYTE_ARRAY_TYPE>
	class Deserializable
	{
	public:
		/**
		 * \brief The destructor.
		 */
		virtual ~Deserializable() = default;

		/**
		 * \brief This function deserializes the object.
		 * \param data the data
		 */
		virtual void deserialize(BYTE_ARRAY_TYPE const& data) = 0;
	};
}
