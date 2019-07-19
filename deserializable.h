#pragma once
namespace ad
{
	/**
	 * @brief This interface is used to deserialize the objects.
	 * 
	 * Objects can be deserialized from the data serialized using the interface Serializable.
	 * It also is possible to deserialize from custom defined data (if such implementation exists).
	 * @tparam bytebuf_t the output type of serialization
	 * @see Serializable
	 */
	template <typename bytebuf_t>
	class Deserializable
	{
	public:
		/**
		 * @brief The destructor.
		 */
		virtual ~Deserializable() = default;

		/**
		 * @brief This function deserializes the object.
		 * @param data the data
		 */
		virtual void deserialize(bytebuf_t const& data) = 0;
	};
}
