#include "invoker_cui_display.hpp"

namespace asterism
{

invoker_cui_display::invoker_cui_display(invoker_t &&invoker, QWidget *parent) noexcept
	: QTextEdit(parent), invoker_(std::move(invoker))
{
	this->process_=std::visit([&](auto &&i){ return i.execute(); }, invoker);
	connect(this->process_, &QProcess::readyReadStandardOutput, this, &invoker_cui_display::read_stdout);
	connect(this->process_, &QProcess::readyReadStandardError, this, &invoker_cui_display::read_stderr);
	connect(this->process_, &QProcess::errorOccurred, [this]() { emit error_occored(); });
	connect(this->process_, qOverload<int, QProcess::ExitStatus>(&QProcess::finished), 
		[this](auto, const auto status){emit finished(status==QProcess::ExitStatus::NormalExit);}
	);
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
		return this->names_[index.row()];
	}
	return QVariant();
}

invoker_t* invoker_list_model::add_invoker(invoker_t &&invoker) noexcept
{
	this->beginInsertRows(QModelIndex(), this->invokers_.size(), this->invokers_.size());
	this->names_.append(std::visit([](const auto &i) { return i.tool_name(); }, invoker));
	this->invokers_.append(std::move(invoker));
	this->endInsertRows();
	return &this->invokers_.last();
}

void invoker_list_model::change_status(const int i, const QString &name) noexcept
{
	if(const auto index=this->createIndex(i, 0); index.isValid())
	{
		this->names_[i]=name;
		this->dataChanged(index, index);
	}
}

invoker_list_widget::invoker_list_widget(QWidget *parent) noexcept
	: QListWidget(parent)
{
	//this->setModel(this->model_);
}

void invoker_list_widget::add_invoker(const invoker_t &invoker) noexcept
{
	//return this->model_->add_invoker(std::move(invoker));
	this->addItem(std::visit([](const auto &i) { return i.tool_name(); }, invoker));
}

void invoker_list_widget::change_status(const int i, const QString &name)
{
	if(0<=i && i<this->count())
	{
		this->item(i)->setText(name);
	}
}

invoker_display_widget::invoker_display_widget(QWidget *parent) noexcept
	: QDialog(parent)
{
	auto *layout=new QHBoxLayout;
	layout->addWidget(this->list_, 1);
	layout->addWidget(this->displays_, 2);
	this->setLayout(layout);
	this->setWindowFlags(Qt::Window);
	this->setWindowTitle(tr("Code Clone Detection Progress"));

	connect(this->list_, &invoker_list_widget::clicked, this, &invoker_display_widget::change_current_page);
}

void invoker_display_widget::change_current_page(const QModelIndex &index) noexcept
{
	this->displays_->setCurrentIndex(index.row());
}

void invoker_display_widget::add_invoker(invoker_t &&invoker) noexcept
{
	QString clone_file=std::visit([](const auto &i) { return i.clone_file(); }, invoker);
	const auto name=std::visit([](const auto &i) { return i.tool_name(); }, invoker);
	this->list_->add_invoker(invoker);
	auto *display=new invoker_cui_display(std::move(invoker), this);
	const int index=this->displays_->addWidget(display);
	
	connect(display, &invoker_cui_display::error_occored, [=]()
		{ emit invoker_status_changed(index, name+" [Error]"); }
	);
	connect(display, &invoker_cui_display::finished, [=](const auto success)
		{
			if(success)
			{
				emit invoker_status_changed(index, name+" [Finished]");
				emit finished_clone_file(clone_file);
			}
		}
	);
	connect(this, &invoker_display_widget::invoker_status_changed, this->list_, &invoker_list_widget::change_status);
	
}

}
