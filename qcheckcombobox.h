#ifndef QCHECKCOMBOBOX_H
#define QCHECKCOMBOBOX_H

#include <QWidget>

class QCheckComboBox : public QWidget
{
	Q_OBJECT

public:
	QCheckComboBox(QStringList aszlist , QWidget *parent=NULL);
	~QCheckComboBox();
public:
	void SetItemCheckStates(int nState);
	int GetItemCheckStates() const;
	int GetItemCount() const;
	QCheckBox* GetCheckBoxFromIndex(int nIndex) const;
private:
	QListWidget *m_List;
	QComboBox *m_Combo;
protected slots:
	void UpdateComboContent();
};

#endif // QCHECKCOMBOBOX_H
