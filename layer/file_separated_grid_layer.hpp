#ifndef FILE_SEPARATED_GRID_LAYER_HPP
#define FILE_SEPARATED_GRID_LAYER_HPP

#include <QVector>

#include "model/file.hpp"


namespace asterism
{

using file_index=QMap<std::weak_ptr<file>, int>;

class grid_coordinate
{
public:
	virtual int to_linear(const std::weak_ptr<file_index> &file_index) const noexcept=0;
};

class grid_2d_coordinate final
	: public grid_coordinate
{
public:
	grid_2d_coordinate(const std::shared_ptr<file> &x, const std::shared_ptr<file> &y) noexcept;

	std::weak_ptr<file> x() const noexcept;
	std::weak_ptr<file> y() const noexcept;

	int to_linear(const std::weak_ptr<file_index> &file_index_ptr) const noexcept override;

	bool operator ==(const grid_2d_coordinate &other) const noexcept;
	bool operator !=(const grid_2d_coordinate &other) const noexcept;

private:
	std::pair<std::weak_ptr<file>, std::weak_ptr<file>> x_y_;

	std::pair<std::weak_ptr<file>, std::weak_ptr<file>> canonical(const std::shared_ptr<file> &x, const std::shared_ptr<file> &y) noexcept;
	std::pair<std::weak_ptr<file>, std::weak_ptr<file>> canonical(std::shared_ptr<file> &&x, std::shared_ptr<file> &&y) noexcept;
};

class grid_1d_coordinate final
	: public grid_coordinate
{
public:
	grid_1d_coordinate(const int i) noexcept;

	int to_linear(const std::weak_ptr<file_index> &file_index) const noexcept override;

	grid_1d_coordinate& operator ++() noexcept;
	grid_1d_coordinate& operator --() noexcept;
	grid_1d_coordinate operator ++(int) noexcept;
	grid_1d_coordinate operator --(int) noexcept;

	bool operator ==(const grid_1d_coordinate &other) const noexcept;
	bool operator !=(const grid_1d_coordinate &other) const noexcept;

private:
	int i_;
};

template <class val_T>
class file_separated_grid_layer
{
public:
	file_separated_grid_layer() noexcept
		: width_(0)
	{}

	file_separated_grid_layer(std::shared_ptr<file_index> &&file_index_ptr) noexcept
		: width_(file_index_ptr->size()), values_(this->required_size())
	{
		file_index_ptr_=std::move(file_index_ptr);
	}

	file_separated_grid_layer(const std::weak_ptr<file_index> &file_index_ptr) noexcept
		: width_(file_index_ptr.lock()->size()), values_(this->required_size())
	{
		file_index_ptr_=std::move(file_index_ptr);
	}

	file_separated_grid_layer(std::shared_ptr<file_index> &&file_index_ptr, const val_T &initial) noexcept
		: width_(file_index_ptr->size()), values_(this->required_size(), initial)
	{
		file_index_ptr_=std::move(file_index_ptr);
	}

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
		return this->values_[coordinate.to_linear(file_index_ptr_)];
	}

	const val_T& operator [](const grid_coordinate &coordiante) const
	{
		return this->values_[coordiante.to_linear(file_index_ptr_)];
	}

	int width() const noexcept
	{
		return file_index_ptr_.lock()->size();
	}

	void update(const std::shared_ptr<file_index> &file_index_ptr) noexcept
	{
		file_index_ptr_=file_index_ptr;
		this->width_=file_index_ptr->size();
		this->values_.resize(this->required_size());
	}

protected:
	int width_;
	QVector<val_T> values_;

	static std::weak_ptr<file_index> file_index_ptr_;

	int required_size() const noexcept
	{
		return this->width_*(this->width_+1)/2;
	}
};

}

#endif // FILE_SEPARATED_GRID_LAYER_HPP
