#pragma once
#include<QAbstractTableModel>
#include<Melodie.h>
#include<vector>
using std::vector;
class TableModel : public	QAbstractTableModel {
private:
	vector<Melodie> melodii;
public:
	TableModel(vector<Melodie>& m) :melodii{ m } {
		std::sort(melodii.begin(), melodii.end(), [&](Melodie& m1, Melodie& m2) {
			return m1.getArtist() < m2.getArtist();
			});
	};

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return melodii.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 6;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Melodie m = melodii[index.row()];
			if (index.column() == 0)
				return QString::number(m.getId());
			if (index.column() == 1)
				return QString::fromStdString(m.getTitlu());
			if (index.column() == 2)
				return QString::fromStdString(m.getArtist());
			if (index.column() == 3)
				return QString::fromStdString(m.getGen());
			if (index.column() == 4) {
				int cnt = 0;
				for (const auto& mel : melodii) {
					if (mel.getArtist() == m.getArtist())
						cnt++;
				}
				return QString::number(cnt);
			}
			if (index.column() == 5) {
				int cnt = 0;
				for (const auto& mel : melodii) {
					if (mel.getGen() == m.getGen())
						cnt++;
				}
				return QString::number(cnt);
			}
		}
		return QVariant{};
	}

	void setMelodii(const vector<Melodie>& mel) {
		this->melodii = mel;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
		emit layoutChanged();
	}

};