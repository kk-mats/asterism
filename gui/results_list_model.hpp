#ifndef RESULTS_LIST_MODEL_HPP
#define RESULTS_LIST_MODEL_HPP

#include <QAbstractListModel>

#include "model/detection_result.hpp"


namespace asterism
{

class results_list_model
	: public QAbstractListModel
{
	Q_OBJECT

public:
	using QAbstractListModel::QAbstractListModel;

	void set_results(const shared_list<detection_result> &results) noexcept;

	int rowCount(const QModelIndex &parent=QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const override;

private:
	shared_list<detection_result> results_list_;
};

}

#endif // RESULTS_LIST_MODEL_HPP