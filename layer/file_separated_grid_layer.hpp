#ifndef FILE_SEPARATED_GRID_LAYER_HPP
#define FILE_SEPARATED_GRID_LAYER_HPP

#include <QVector>

#include "model/file.hpp"


namespace asterism
{

class grid_coordinate
{
public:
	virtual uint32_t to_linear() const noexcept=0;
};

class grid_2d_coordinate final
	: public grid_coordinate
{
public:
	grid_2d_coordinate(const file::id_t &x, const file::id_t &y) noexcept;
	grid_2d_coordinate(file::id_t &&x, file::id_t &&y) noexcept;

	file::id_t x() const noexcept;
	file::id_t y() const noexcept;

	uint32_t to_linear() const noexcept override;

	bool operator ==(const grid_2d_coordinate &other) const noexcept;
	bool operator !=(const grid_2d_coordinate &other) const noexcept;

private:
	QPair<file::id_t, file::id_t> x_y_;

	QPair<file::id_t, file::id_t> canonical(const file::id_t &x, const file::id_t &y) noexcept;
	QPair<file::id_t, file::id_t> canonical(file::id_t &&x, file::id_t &&y) noexcept;
};

class grid_1d_coordinate final
	: public grid_coordinate
{
public:
	grid_1d_coordinate(const file::id_t &i) noexcept;
	grid_1d_coordinate(file::id_t &&i) noexcept;

	file::id_t index() const noexcept;

	uint32_t to_linear() const noexcept override;

	grid_1d_coordinate& operator ++() noexcept;
	grid_1d_coordinate& operator --() noexcept;
	grid_1d_coordinate operator ++(int) noexcept;
	grid_1d_coordinate operator --(int) noexcept;

	bool operator ==(const grid_1d_coordinate &other) const noexcept;
	bool operator !=(const grid_1d_coordinate &other) const noexcept;

private:
	file::id_t i_;
};

template <class val_T>
class file_separated_grid_layer
{
public:
	file_separated_grid_layer() noexcept
	{}

	file_separated_grid_layer(const uint32_t width) noexcept
		: width_(width), values_(width*(width+1)/2)
	{}

	file_separated_grid_layer(const uint32_t width, const val_T &initial) noexcept
		: width_(width), values_(width*(width+1)/2, initial)
	{}

	auto begin() const noexcept
	{
		return this->values_.begin();
	}

	auto& begin() noexcept
	{
		return this->values_.begin();
	}

	auto begin1d() const noexcept
	{
		return grid_1d_coordinate(0);
	}

	auto end() const noexcept
	{
		return this->values_.end();
	}

	auto& end() noexcept
	{
		return this->values_.end();
	}

	auto end1d() const noexcept
	{
		return grid_1d_coordinate(this->values_.size()-1);
	}

	val_T& operator [](const grid_coordinate &coordinate)
	{
		return this->values_[coordinate.to_linear()];
	}

	const val_T& operator [](const grid_coordinate &coordiante) const
	{
		return this->values_[coordiante.to_linear()];
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
