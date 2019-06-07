#include "invoker_cui_display.hpp"

namespace asterism
{

invoker_cui_display::invoker_cui_display(QProcess *process, QWidget *parent) noexcept
	: QTextEdit(parent), process_(process)
{
	connect(process, &QProcess::readyReadStandardOutput, this, &invoker_cui_display::read_stdout);
	connect(process, &QProcess::readyReadStandardError, this, &invoker_cui_display::read_stderr);
}

void invoker_cui_display::read_stdout() noexcept
{
	this->append(QString::fromLocal8Bit(this->process_->readAllStandardOutput()));
}

void invoker_cui_display::read_stderr() noexcept
{
	this->append(QString::fromLocal8Bit(this->process_->readAllStandardError()));
}


int invoker_list_model::columnCount(const QModelIndex &parent) const noexcept
{
	return this->invokers_.size();
}

int invoker_list_model::rowCount(const QModelIndex &parent) const noexcept
{
	return 1;
}

QVariant invoker_list_model::data(const QModelIndex &index, int role) const noexcept
{
	if(index.isValid() && role==Qt::DisplayRole)
	{
		return std::visit([](const auto &i) { return i.tool_name(); }, this->invokers_[index.row()]);
	}
	return QVariant();
}

void invoker_list_model::add_invoker(invoker_t &&invoker) noexcept
{
	this->beginInsertRows(QModelIndex(), this->invokers_.size(), this->invokers_.size());
	this->invokers_.push_back(std::move(invoker));
	this->endInsertRows();
}

invoker_list_widget::invoker_list_widget(QWidget *parent) noexcept
	: QListView(parent)
{
	this->setModel(this->model_);
}

void invoker_list_widget::add_invoker(invoker_t &&invoker)
{
	this->model_->add_invoker(std::move(invoker));
}

invoker_display_widget::invoker_display_widget(QWidget *parent) noexcept
	: QDialog(parent)
{
	auto *layout=new QHBoxLayout;
	layout->addWidget(this->list_, 1);
	layout->addWidget(this->displays_, 2);
	this->setLayout(layout);

	connect(this->list_, &invoker_list_widget::clicked, this, &invoker_display_widget::change_current_page);
}

void invoker_display_widget::change_current_page(const QModelIndex &index) noexcept
{
	this->displays_->setCurrentIndex(index.row());
}

void invoker_display_widget::add_invoker(invoker_t &&invoker) noexcept
{
	this->displays_->addWidget(new invoker_cui_display(std::visit([](auto &&i) { return i.execute(); }, invoker), this));
	this->list_->add_invoker(std::move(invoker));
}

}
