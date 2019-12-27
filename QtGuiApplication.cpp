#include "QtGuiApplication.h"
#include <QString>
#include <QMessageBox>
#include <set>

using namespace std;

QtGuiApplication::QtGuiApplication(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(Main()));
}
//	Основной слот
void QtGuiApplication::Main(){

	//	Получение данных
	QString Qtext = ui.plainTextEdit->toPlainText();

	string data = Qtext.toLocal8Bit().constData();

	//	При пустых входных данных вывод соответствующей ошибки
	if (data.length() == 0) {
		Error("Empty data!");
		return;
	}

	multiset <char> mst;


	//	Заполенеие multiset только буквами английского алфавита
	for (int i = 0; i < data.length(); i++) {

		data[i] = tolower(data[i]);

		if (data[i] >= 'a' && data[i] <= 'z') {
			mst.insert(data[i]);
		}

	}

	if (mst.empty()) {
		Error("No letters!");
		return;
	}

	auto mst_end = mst.end();

	// prev - предыдущий элемет в списке multiset
	auto prev = *mst.begin();

	string result_text = "";


	//	Обход multiset  
	for (auto elem = mst.begin(); elem != mst_end; elem++) {

		//	Условие для избежания повторных выводов ("буква" - "количество")
		if (prev == *elem && elem != mst.begin()) {
			continue;
		}
		prev = *elem;

		//	Формирование результирующей строки
		result_text += *elem ;
		result_text += " - ";
		result_text += to_string(mst.count(*elem));
		result_text += '\n';

	}
	//	Вывод данных
    ui.textBrowser->setText(QString::fromStdString(result_text));
}

void QtGuiApplication::Error(QString mess) {
	ui.textBrowser->setPlainText("");
	ui.plainTextEdit->setPlainText("");
	QMessageBox msgbox;
	msgbox.setWindowTitle("Error");
	msgbox.setText(mess);
	msgbox.exec();
}
