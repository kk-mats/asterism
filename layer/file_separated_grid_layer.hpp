#ifndef FILE_SEPARATED_GRID_LAYER_HPP
#define FILE_SEPARATED_GRID_LAYER_HPP

#include <QVector>

#include "model/clone_pair.hpp"

namespace asterism
{

class grid_coordinate
{

public:
	virtual int to_linear() const noexcept=0;
};

class grid_1d_coordinate final
	: public grid_coordinate
{
public:
	grid_1d_coordinate(const int i) noexcept;

	int to_linear() const noexcept override;

	grid_1d_coordinate& operator ++() noexcept;
	grid_1d_coordinate& operator --() noexcept;
	grid_1d_coordinate operator ++(int) noexcept;
	grid_1d_coordinate operator --(int) noexcept;

	bool operator ==(const grid_1d_coordinate &other) const noexcept;
	bool operator !=(const grid_1d_coordinate &other) const noexcept;

private:
	int i_;
};

class grid_2d_coordinate final
	: public grid_coordinate
{
public:
	grid_2d_coordinate(const std::shared_ptr<file> &x, const std::shared_ptr<file> &y) noexcept;

	int x() const noexcept;
	int y() const noexcept;

	int to_linear() const noexcept override;
	static grid_1d_coordinate to_linear(const int x, const int y) noexcept;

	bool operator ==(const grid_2d_coordinate &other) const noexcept;
	bool operator !=(const grid_2d_coordinate &other) const noexcept;

private:
	std::pair<int, int> x_y_;
};

template <class val_T>
class file_separated_grid_layer
{
public:
	file_separated_grid_layer() noexcept
		: width_(0)
	{}

	file_separated_grid_layer(const int file_size) noexcept
		: width_(file_size), values_(this->required_size(this->width_))
	{}

	file_separated_grid_layer(const int file_size, const val_T &initial) noexcept
		: width_(file_size), values_(this->required_size(this->width_), initial)
	{}

	auto begin() const noexcept
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

	auto end1d() const noexcept
	{
		return grid_1d_coordinate(this->values_.size());
	}

	val_T& operator [](const grid_coordinate &coordinate)
	{
		return this->values_[coordinate.to_linear()];
	}

	const val_T& operator [](const grid_coordinate &coordiante) const
	{
		return this->values_[coordiante.to_linear()];
	}

	const val_T &operator [](const int i) const
	{
		return this->values_[i];
	}

	int width() const noexcept
	{
		return this->width_;
	}

	int size() const noexcept
	{
		return this->values_.size();
	}

	void resize(const int width) noexcept
	{
		this->width_=width;
		this->values_.clear();
		this->values_.resize(this->required_size(this->width_));
	}

protected:
	int width_=0;
	QVector<val_T> values_;

	int required_size(const int width) const noexcept
	{
		return width*(width+1)/2;
	}
};

}

#endif // FILE_SEPARATED_GRID_LAYER_HPP
