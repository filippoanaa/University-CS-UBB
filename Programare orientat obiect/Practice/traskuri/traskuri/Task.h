#pragma once
#include<string>
#include<vector>
using std::vector;
using std::string;
class Task
{
private:
	int id;
	string descriere, stare;
	vector<string> listaProgramatori;
public:
	//constructor
	Task(int id, string desc, vector<string> listaProgramatori, string stare) :id{ id }, descriere{ desc }, listaProgramatori{ listaProgramatori }, stare{ stare } {};

    /*
   * Getter pentru id
   * return type: int - ID-ul task-ului
   */
    int getId() const;

    /*
    * Getter pentru descriere
    * return type: string - descrierea task-ului
    */
    string getDesc() const;

    /*
    * Getter pentru lista de programatori
    * return type: vector<string> - lista programatorilor asignati task-ului
    */
    vector<string> getProgramatori() const;

    /*
    * Getter pentru stare
    * return type: string - starea curenta a task-ului
    */
    string getStare() const;

    /*
    * Setter pentru stare
    * seteaza o noua stare pentru task
    * stareNoua - string, noua stare a task-ului
    */
    void setStare(const string& stareNoua);

