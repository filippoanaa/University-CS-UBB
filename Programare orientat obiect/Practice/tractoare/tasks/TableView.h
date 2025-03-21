#pragma once
#include<Service.h>
#include<QAbstractTableModel>
#include<vector>
using namespace std;

class Table : public QAbstractTableModel {
	vector<Tractor> tractoare;
	string filtru;
public:
	Table(vector<Tractor>& tractoare) :tractoare{ tractoare } {
		//sortTractoare();
	};
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return tractoare.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Tractor t = tractoare[index.row()];
			if (index.column() == 0)
				return QString::number(t.getId());
			else if (index.column() == 1)
				return QString::fromStdString(t.getDenumire());
			else if (index.column() == 2)
				return QString::fromStdString(t.getTip());
			else if (index.column() == 3)
				return QString::number(t.getNrRoti());
			else if (index.column() == 4) {
				int cnt = std::count_if(tractoare.begin(), tractoare.end(), [&t](const Tractor& tr) {
					return t.getTip() == tr.getTip();
					});
				return QString::number(cnt);
			}
		}
		if (role == Qt::BackgroundRole) {
			const Tractor& t = tractoare[index.row()];
			if (t.getTip() == filtru)
				return QBrush(Qt::red);
		}
		return QVariant{};
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			if (orientation == Qt::Horizontal) {
				switch (section) {
				case 0:
					return QString("ID");
				case 1:
					return QString("Denumire");
				case 2:
					return QString("Tip");
				case 3:
					return QString("Nr roti");
				case 4:
					return QString("Acelasi tip");
				default:
					return QVariant{};
				}
			}
		}
		return QVariant{};
	}
	void setTractoare(const vector<Tractor>& tractoare) {
		this->tractoare = tractoare;
		//sortTractoare();
		auto stangaSus = createIndex(0, 0);
		auto dreaptaJos = createIndex(rowCount(), columnCount());
		emit dataChanged(stangaSus, dreaptaJos);
		emit layoutChanged();
	}

	void setTipFiltru(const string& tip) {
		filtru = tip;
		auto stangaSus = createIndex(0, 0);
		auto dreaptaJos = createIndex(rowCount(), columnCount());
		emit dataChanged(stangaSus, dreaptaJos);

	}
};