#pragma once
#include<QAbstractTableModel>
#include<String>
#include<vector>
#include<Melodie.h>
using std::vector;
using std::string;
class TableModel : public QAbstractTableModel {
private:
	vector<Melodie> melodii;
public:
	TableModel(vector<Melodie>& melodii) :melodii{ melodii } {
		std::sort(this->melodii.begin(), this->melodii.end(), [&](Melodie& m1, Melodie& m2) {
			return m1.getRank() < m2.getRank();
			});
	};

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return melodii.size();
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Melodie m = melodii[index.row()];
			if (index.column() == 0) {
				return QString::number(m.getId());
			}
			if (index.column() == 1) {
				return QString::fromStdString(m.getTitlu());
			}
			if (index.column() == 2) {
				return QString::fromStdString(m.getArtist());
			}
			if (index.column() == 3) {
				return QString::number(m.getRank());
			}
			if (index.column() == 4) {
				int cnt = 0;
				for (int i = 0; i < melodii.size(); i++) {
					if (melodii[i].getRank() == m.getRank())
						cnt++;
				}
				return QString::number(cnt);
			}
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
					return QString("Titlu"); 
				case 2:
					return QString("Artist"); 
				case 3:
					return QString("Rank");  
				case 4:
					return QString("Count");  
				default:
					return QVariant{};
				}
			}
		}
		return QVariant{};
	}

	void setMelodii(vector<Melodie>& v) {
		this->melodii = v;
		auto topLeft = createIndex(0, 0);
		auto bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
	}


};
