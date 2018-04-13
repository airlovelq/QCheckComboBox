#include "stdafx.h"
#include "qcheckcombobox.h"

QCheckComboBox::QCheckComboBox(QStringList aszlist , QWidget *parent)
	: QWidget(parent)
{
	m_Combo = new QComboBox(this);
	QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_Combo);
    setLayout(mainLayout);

	m_List = new QListWidget(this);
	for ( int i = 0 ; i<aszlist.size() ; i++ )
	{
	    QListWidgetItem *item = new QListWidgetItem();
		//item->setCheckState(Qt::Unchecked);
		//item->setText(aszlist.at(i));
		
		m_List->addItem(item);
		QCheckBox *box = new QCheckBox();
		box->setText(aszlist.at(i));
		m_List->setItemWidget(item,box);
		connect(box,&QCheckBox::stateChanged,this,&QCheckComboBox::UpdateComboContent);
	}
	m_Combo->setModel(m_List->model());
	m_Combo->setView(m_List);
	m_Combo->setEditable(true);
	QLineEdit* lineEdit = m_Combo->lineEdit();
    if(lineEdit)
    {
        lineEdit->setReadOnly(true);
    }
	
}

QCheckComboBox::~QCheckComboBox()
{

}

void QCheckComboBox::UpdateComboContent()
{
	QString str ;
	for ( int i= 0 ; i<m_List->count() ; i++ )
	{
		
		QListWidgetItem *item = m_List->item(i);
		QCheckBox *box = (QCheckBox*)m_List->itemWidget(item);
		if ( box->checkState() == Qt::Checked )
		{
			str += box->text();
			str += ";";
		}
	}
	str = str.mid(0,str.size()-1);
	m_Combo->lineEdit()->setText(str);
}

void QCheckComboBox::SetItemCheckStates(int nState)
{
	for ( int i = 0 ; i < m_List->count() ; i ++ )
	{
		if ( nState % 2 == 1 )
		{
			QListWidgetItem *item = m_List->item(i);
			QCheckBox *box = (QCheckBox*)m_List->itemWidget(item);
			box->setChecked(true);
		}
		nState /= 2 ;
	}
	UpdateComboContent();
}

int QCheckComboBox::GetItemCheckStates() const
{
	int nState = 0;
	for ( int i = 0 ; i < m_List->count() ; i ++ )
	{
		QListWidgetItem *item = m_List->item(i);
		QCheckBox *box = (QCheckBox*)m_List->itemWidget(item);
		nState += int(box->isChecked()) * pow(float(2.0),i);
	}
	return nState;
}

int QCheckComboBox::GetItemCount() const
{
	return m_List->count();
}

QCheckBox* QCheckComboBox::GetCheckBoxFromIndex(int nIndex) const
{
	if (( nIndex<0 ) || ( nIndex>m_List->count()-1 ))
	    return NULL;
	QListWidgetItem *item = m_List->item(nIndex);
	QCheckBox *box = (QCheckBox*)m_List->itemWidget(item);
	return box;
}