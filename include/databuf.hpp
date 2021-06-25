#ifndef WS_DATASTREAM_BUF_H_

#define WS_DATASTREAM_BUF_H_
#include <algorithm>
#include <cstring>
#include <stdexcept>
#include <streambuf>
#include <vector>
namespace buffer {

	namespace buf {
		class mutable_buffer
		{
		public:
			/// Construct an empty buffer.
			mutable_buffer() noexcept
				: data_(0),
				size_(0)
			{
			}

			/// Construct a buffer to represent a given memory range.
			mutable_buffer(void* data, std::size_t size) noexcept
				: data_(data),
				size_(size)
			{
			}

			/// Get a pointer to the beginning of the memory range.
			void* data() const noexcept
			{
				return data_;
			}

			/// Get the size of the memory range.
			std::size_t size() const noexcept
			{
				return size_;
			}

			/// Move the start of the buffer by the specified number of bytes.
			mutable_buffer& operator+=(std::size_t n) noexcept
			{
				std::size_t offset = n < size_ ? n : size_;
				data_ = static_cast<char*>(data_) + offset;
				size_ -= offset;
				return *this;
			}

		private:
			void* data_;
			std::size_t size_;
		};

		class const_buffer
		{
		public:
			/// Construct an empty buffer.
			const_buffer() noexcept
				: data_(0),
				size_(0)
			{
			}

			/// Construct a buffer to represent a given memory range.
			const_buffer(const void* data, std::size_t size) noexcept
				: data_(data),
				size_(size)
			{
			}

			/// Construct a non-modifiable buffer from a modifiable one.
			const_buffer(const mutable_buffer& b) noexcept
				: data_(b.data()),
				size_(b.size())

			{
			}



			/// Get a pointer to the beginning of the memory range.
			const void* data() const noexcept
			{
				return data_;
			}

			/// Get the size of the memory range.
			std::size_t size() const noexcept
			{
				return size_;
			}

			/// Move the start of the buffer by the specified number of bytes.
			const_buffer& operator+=(std::size_t n) noexcept
			{
				std::size_t offset = n < size_ ? n : size_;
				data_ = static_cast<const char*>(data_) + offset;
				size_ -= offset;
				return *this;
			}

		private:
			const void* data_;
			std::size_t size_;

		};

		class const_buffers_1
			: public const_buffer
		{
		public:
			/// The type for each element in the list of buffers.
			typedef const_buffer value_type;

			/// A random-access iterator type that may be used to read elements.
			typedef const const_buffer* const_iterator;

			/// Construct to represent a given memory range.
			const_buffers_1(const void* data, std::size_t size) noexcept
				: const_buffer(data, size)
			{
			}



			/// Construct to represent a single non-modifiable buffer.
			explicit const_buffers_1(const const_buffer& b) noexcept
				: const_buffer(b)
			{
			}

			/// Get a random-access iterator to the first element.
			const_iterator begin() const noexcept
			{
				return this;
			}

			/// Get a random-access iterator for one past the last element.
			const_iterator end() const noexcept
			{
				return begin() + 1;
			}
		};

		class null_buffers
		{
		public:
			/// The type for each element in the list of buffers.
			typedef mutable_buffer value_type;

			/// A random-access iterator type that may be used to read elements.
			typedef const mutable_buffer* const_iterator;

			/// Get a random-access iterator to the first element.
			const_iterator begin() const noexcept
			{
				return &buf_;
			}

			/// Get a random-access iterator for one past the last element.
			const_iterator end() const noexcept
			{
				return &buf_;
			}

		private:
			mutable_buffer buf_;
		};

		class ubuffer {
		public:
			size_t size;
			std::unique_ptr<char[]> data;

		};

		//#if !defined(GENERATING_DOCUMENTATION)
		template <typename Allocator = std::allocator<char> >
		//#else
		//template <typename Allocator>
		//#endif
		//
		class MyDataBuf : public std::streambuf {
		public:
			/// Construct a MyDataBuf object.
	  /**
	   * Constructs a streambuf with the specified maximum size. The initial size
	   * of the streambuf's input sequence is 0.
	   */
			explicit MyDataBuf(
				std::size_t maximum_size = (std::numeric_limits<std::size_t>::max)(),
				const Allocator& allocator = Allocator())
				: max_size_(maximum_size),
				buffer_(allocator)
			{
				/*std::size_t pend = (std::min<std::size_t>)(max_size_, buffer_delta);
				buffer_.resize((std::max<std::size_t>)(pend, 1));
				setg(&buffer_[0], &buffer_[0], &buffer_[0]);
				setp(&buffer_[0], &buffer_[0] + pend);*/
				std::size_t pend = (std::min<std::size_t>)(max_size_, buffer_delta);
				buffer_.resize((std::max<std::size_t>)(pend, 1));
				this->reset();
				//this->res
			}

			void reinit() {
				std::size_t pend = (std::min<std::size_t>)((std::numeric_limits<std::size_t>::max)(), buffer_delta);
				buffer_.resize((std::max<std::size_t>)(pend, 1));
				setg(&buffer_[0], &buffer_[0], &buffer_[0]);
				setp(&buffer_[0], &buffer_[0] + this->buffer_.capacity());
			}

			void reset() {
				
				setg(&buffer_[0], &buffer_[0], &buffer_[0]);
				setp(&buffer_[0], &buffer_[0] + this->buffer_.capacity());
			}

			/// Get the size of the input sequence.
			/**
			 * @returns The size of the input sequence. The value is equal to that
			 * calculated for @c s in the following code:
			 * @code
			 * size_t s = 0;
			 * const_buffers_type bufs = data();
			 * const_buffers_type::const_iterator i = bufs.begin();
			 * while (i != bufs.end())
			 * {
			 *   const_buffer buf(*i++);
			 *   s += buf.size();
			 * }
			 * @endcode
			 */
			std::size_t size() const noexcept
			{
				return pptr() - gptr();
			}


			ubuffer data() {
				ubuffer ub;
				ub.size = this->size();
				char * d = new char[ub.size];				
				std::istream iss(this);
				iss.read(d, ub.size);
				ub.data = std::unique_ptr<char[]>(d);
				return ub;
			}

			std::string string() {
				try {
					size_t size = this->size();
					std::string s;
					s.resize(size);
					std::istream iss(this);
					iss.read(&s[0], size);
					return s;
				}
				catch (...) {
					return std::string();
				}
			}

			/// Get the maximum size of the MyDataBuf.
			/**
			 * @returns The allowed maximum of the sum of the sizes of the input sequence
			 * and output sequence.
			 */
			std::size_t max_size() const noexcept
			{
				return max_size_;
			}

			/// Get the current capacity of the MyDataBuf.
			/**
			 * @returns The current total capacity of the streambuf, i.e. for both the
			 * input sequence and output sequence.
			 */
			std::size_t capacity() const noexcept
			{
				return buffer_.capacity();
			}

			/// Get a list of buffers that represents the input sequence.
			/**
			 * @returns An object of type @c const_buffers_type that satisfies
			 * ConstBufferSequence requirements, representing all character arrays in the
			 * input sequence.
			 *
			 * @note The returned object is invalidated by any @c MyDataBuf member
			 * function that modifies the input sequence or output sequence.
			 */
		/*	const_buffers_1 data() const noexcept
			{
				return const_buffers_1(const_buffer(gptr(),
					(pptr() - gptr()) * sizeof(char_type)));
			}*/

			/// Get a list of buffers that represents the output sequence, with the given
			/// size.
			/**
			 * Ensures that the output sequence can accommodate @c n characters,
			 * reallocating character array objects as necessary.
			 *
			 * @returns An object of type @c const_buffers_1 that satisfies
			 * MutableBufferSequence requirements, representing character array objects
			 * at the start of the output sequence such that the sum of the buffer sizes
			 * is @c n.
			 *
			 * @throws std::length_error If <tt>size() + n > max_size()</tt>.
			 *
			 * @note The returned object is invalidated by any @c MyDataBuf member
			 * function that modifies the input sequence or output sequence.
			 */
			mutable_buffer prepare(std::size_t n)
			{
				reserve(n);
				return mutable_buffer(mutable_buffer(
					pptr(), n * sizeof(char_type)));
			}

			char* begin() const{
				return gptr();
			}

			/// Move characters from the output sequence to the input sequence.
			/**
			 * Appends @c n characters from the start of the output sequence to the input
			 * sequence. The beginning of the output sequence is advanced by @c n
			 * characters.
			 *
			 * Requires a preceding call <tt>prepare(x)</tt> where <tt>x >= n</tt>, and
			 * no intervening operations that modify the input or output sequence.
			 *
			 * @note If @c n is greater than the size of the output sequence, the entire
			 * output sequence is moved to the input sequence and no error is issued.
			 */
			void commit(std::size_t n)
			{
				n = std::min<std::size_t>(n, epptr() - pptr());
				pbump(static_cast<int>(n));
				setg(eback(), gptr(), pptr());
			}

		/*	char * begin() {
				return this->pb
			}*/

			/// Remove characters from the input sequence.
			/**
			 * Removes @c n characters from the beginning of the input sequence.
			 *
			 * @note If @c n is greater than the size of the input sequence, the entire
			 * input sequence is consumed and no error is issued.
			 */
			void consume(std::size_t n)
			{
				if (egptr() < pptr())
					setg(&buffer_[0], gptr(), pptr());
				if (gptr() + n > pptr())
					n = pptr() - gptr();
				gbump(static_cast<int>(n));
			}

		protected:
			enum { buffer_delta = 128 };

			/// Override std::streambuf behaviour.
			/**
			 * Behaves according to the specification of @c std::streambuf::underflow().
			 */
			int_type underflow()
			{
				if (gptr() < pptr())
				{
					setg(&buffer_[0], gptr(), pptr());
					return traits_type::to_int_type(*gptr());
				}
				else
				{
					return traits_type::eof();
				}
			}

			/// Override std::streambuf behaviour.
			/**
			 * Behaves according to the specification of @c std::streambuf::overflow(),
			 * with the specialisation that @c std::length_error is thrown if appending
			 * the character to the input sequence would require the condition
			 * <tt>size() > max_size()</tt> to be true.
			 */
			int_type overflow(int_type c)
			{
				if (!traits_type::eq_int_type(c, traits_type::eof()))
				{
					if (pptr() == epptr())
					{
						std::size_t buffer_size = pptr() - gptr();
						if (buffer_size < max_size_ && max_size_ - buffer_size < buffer_delta)
						{
							reserve(max_size_ - buffer_size);
						}
						else
						{
							reserve(buffer_delta);
						}
					}

					*pptr() = traits_type::to_char_type(c);
					pbump(1);
					return c;
				}

				return traits_type::not_eof(c);
			}

			void reserve(std::size_t n)
			{
				// Get current stream positions as offsets.
				std::size_t gnext = gptr() - &buffer_[0];
				std::size_t pnext = pptr() - &buffer_[0];
				std::size_t pend = epptr() - &buffer_[0];

				// Check if there is already enough space in the put area.
				if (n <= pend - pnext)
				{
					return;
				}

				// Shift existing contents of get area to start of buffer.
				if (gnext > 0)
				{
					pnext -= gnext;
					std::memmove(&buffer_[0], &buffer_[0] + gnext, pnext);
				}

				// Ensure buffer is large enough to hold at least the specified size.
				if (n > pend - pnext)
				{
					if (n <= max_size_ && pnext <= max_size_ - n)
					{
						pend = pnext + n;
						buffer_.resize((std::max<std::size_t>)(pend, 1));
					}
					else
					{

						return throw std::exception("ws::MyDataBuf too long");
					}
				}

				// Update stream positions.
				setg(&buffer_[0], &buffer_[0], &buffer_[0] + pnext);
				setp(&buffer_[0] + pnext, &buffer_[0] + pend);
			}

		private:
			std::size_t max_size_;
			std::vector<char_type, Allocator> buffer_;

			// Helper function to get the preferred size for reading data.
			friend std::size_t read_size_helper(
				MyDataBuf& sb, std::size_t max_size)
			{
				return std::min<std::size_t>(
					std::max<std::size_t>(512, sb.buffer_.capacity() - sb.size()),
					std::min<std::size_t>(max_size, sb.max_size() - sb.size()));
			}
		};

	}

	typedef buf::MyDataBuf<> Databuf;
}

#endif // !WS_MESSAGE_H_
