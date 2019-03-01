#ifndef FILE_SEPARATED_GRID_LAYER_HPP
#define FILE_SEPARATED_GRID_LAYER_HPP

#include <QVector>

#include "model/file.hpp"


namespace asterism
{

class grid_coordinate
{
public:
	grid_coordinate(const file::id_t &x, const file::id_t &y) noexcept;
	grid_coordinate(file::id_t &&x, file::id_t &&y) noexcept;

	uint32_t to_1d(const uint32_t width) const noexcept;

private:
	file::id_t x_, y_;
};


template <class val_T>
class file_separated_grid_layer
{
public:
	file_separated_grid_layer(const uint32_t width) noexcept
		: width_(width), values_(width*(width+1)/2)
	{}

	file_separated_grid_layer(const uint32_t width, const val_T &initial) noexcept
		: width_(width), values_(width*(width+1)/2, initial)
	{}

	auto begin() noexcept
	{
		return this->values_.begin();
	}

	auto cbegin() const noexcept
	{
		return this->values_.cbegin();
	}

	auto end() noexcept
	{
		return this->values_.end();
	}

	auto cend() const noexcept
	{
		return this->values_.cend();
	}

	val_T& operator [](const grid_coordinate &coordinate)
	{
		return this->values_[coordinate.to_1d(this->width_)];
	}

	const val_T& operator [](const grid_coordinate &coordiante) const
	{
		return this->values_[coordiante.to_1d(this->width_)];
	}

	uint32_t width() const noexcept
	{
		return this->width_;
	}

protected:
	uint32_t width_;
	QVector<val_T> values_;
};

}

#endif // FILE_SEPARATED_GRID_LAYER_HPP
