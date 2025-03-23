#include "service.h"
#include<algorithm>

std::vector<Device> Service::sorteazaModel()
{
	auto all = getAllDevices();
	sort(all.begin(), all.end(), [&](Device& d1, Device& d2) {
		return d1.getModel() < d2.getModel();
		});
	return all;
}

std::vector<Device> Service::sorteazaAn()
{
	auto all = getAllDevices();
	sort(all.begin(), all.end(), [&](Device& d1, Device& d2) {
		return d1.getAn() < d2.getAn();
		});
	return all;

}
