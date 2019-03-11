#include "detection_result.hpp"

namespace asterism
{

detection_result::detection_result() noexcept
	: id_(new_id())
{}

detection_result::id_t detection_result::id() const noexcept
{
	return this->id_;
}

result_context detection_result::context() const noexcept
{
	return this->context_;
}

QList<clone_pair> detection_result::clone_pairs() const noexcept
{
	return this->clone_pair_table_.values();
}

clone_pair detection_result::clone_pair_of(const clone_pair::id_t &id) const noexcept
{
	return this->clone_pair_table_[id];
}

clone_pair::id_t detection_result::add(const clone_pair &clone_pair) noexcept
{
	auto p=clone_pair;
	return this->add(std::move(p));
}

clone_pair::id_t detection_result::add(clone_pair &&clone_pair) noexcept
{
	const auto id=clone_pair.id();
	this->clone_pair_table_[id]=std::move(clone_pair);
	return id;
}

QJsonValue detection_result::to_qjson() const noexcept
{
	QJsonArray json_clone_pairs_array;
	for(const auto &p:this->clone_pair_table_)
	{
		json_clone_pairs_array.append(p.to_qjson());
	}

	return QJsonObject
	{
		{"result_id", int(this->id_)},
		{"clone_pairs", json_clone_pairs_array}
	};
}

uint32_t detection_result::id_ctr_=0;

detection_result::id_t detection_result::new_id() noexcept
{
	auto id=detection_result::id_t(id_ctr_);
	++id_ctr_;
	return id;
}

detection_results::detection_results(const QString &target_path) noexcept
{

}

file::id_t detection_results::add(file &&file) noexcept
{
	const auto id=file.id();
	this->file_table_[id]=std::move(file);
	return id;
}

detection_result::id_t detection_results::add(detection_result &&result) noexcept
{
	const auto id=result.id();
	this->result_table_[id]=std::move(result);
	return id;
}

QJsonValue detection_results::to_qjson() const noexcept
{
	QJsonArray files, results;
	for(const auto &f:this->file_table_)
	{
		files.append(f.to_qjson());
	}
	for(const auto &r:this->result_table_)
	{
		results.append(r.to_qjson());
	}

	return QJsonObject
	{
		{"global",
			{"target", 			}
		}
	};
}

bool detection_results::from_qjson(const QJsonObject &json) const noexcept
{

}

}
