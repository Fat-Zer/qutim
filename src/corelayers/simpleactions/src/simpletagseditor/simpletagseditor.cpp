#include "simpletagseditor.h"
#include <qutim/contact.h>
#include <qutim/icon.h>
#include <qutim/servicemanager.h>
#include <qutim/account.h>
#include "ui_simpletagseditor.h"

namespace Core {

SimpleTagsEditor::SimpleTagsEditor(Contact *contact) :
	QDialog(),
	ui(new Ui::SimpleTagsEditor),
	m_contact(contact)
{
	ui->setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	ui->addButton->setIcon(Icon("document-new"));
	setWindowIcon(Icon("feed-subscribe"));
	setWindowTitle(tr("Edit tags for %1").arg(contact->title()));
}

SimpleTagsEditor::~SimpleTagsEditor()
{
	delete ui;
}

void SimpleTagsEditor::accept()
{
	save();
	QDialog::accept();
}

void SimpleTagsEditor::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void SimpleTagsEditor::load()
{
	QStringList tags;
	// Try to request tag list from the contact model
	if (QObject *model = ServiceManager::getByName("ContactModel")) {
		model->metaObject()->invokeMethod(model, "tags",
				Qt::AutoConnection, Q_RETURN_ARG(QStringList, tags));
	}

	if (tags.isEmpty()) {
		// There is no ContactModel service, or it does not have
		// tags() method, so we pass all contacts to gather tag list.
		// It is slow, but it's better than nothing.
		QSet<QString> tagsSet;
		foreach (Account *account, Account::all()) {
			foreach (Contact *contact, account->findChildren<Contact*>()) {
				tagsSet += contact->tags().toSet();
			}
		}
		tags = tagsSet.toList();
	}

	QStringList contactTags = m_contact->tags();
	ui->listWidget->clear();
	foreach (const QString &tag, tags) {
		QListWidgetItem *item = new QListWidgetItem(tag,ui->listWidget);
		item->setCheckState(contactTags.contains(tag) ? Qt::Checked : Qt::Unchecked);
	}
}

void SimpleTagsEditor::save()
{
	QSet<QString> tags;
	for (int index = 0;index!=ui->listWidget->count();index++) {
		if (ui->listWidget->item(index)->checkState() == Qt::Checked)
			tags << ui->listWidget->item(index)->text();
	}
	m_contact->setTags(tags.toList());
}

void Core::SimpleTagsEditor::on_addButton_clicked()
{
	QListWidgetItem *item = new QListWidgetItem(ui->lineEdit->text(),ui->listWidget);
	item->setCheckState(Qt::Unchecked);
	ui->lineEdit->clear();
}

}
