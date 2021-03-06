#include <QList>

#include "addressbookcontroller.h"
#include "contact.h"
#include "qtcontactlist.h"

#include <string>
#include<string.h>

/*
Constructor
    Populate list from passed in recordset

Populate List
    For each item in recordset
        Get the First Name & Last Name
        Create a new entry on the list with those name combined
*/

QtContactList::QtContactList(AddressBookModel &model, QWidget *parent) : 
    QListWidget(parent), dataSource(model)
{
    setSelectionMode(QAbstractItemView::SingleSelection);

    connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(dispatchListItemContactId()));

    populateList();

    setCurrentRow(0, QItemSelectionModel::SelectCurrent);

}

void QtContactList::populateList(Contact::ContactId selected)
{

    //Get all the contacts from the data store
    Contact::ContactRecordSet allContacts;
    dataSource.getAllContacts(allContacts);
    
    Contact::ContactRecordSet::const_iterator it;

    std::string listTitle = "";
    QListWidgetItem *newItem;
    QListWidgetItem *selectedItem;
    
    //Create new list items for each contact
    for(it = allContacts.begin();it != allContacts.end();it++)
    {
        listTitle = it->firstName + " " +  it->lastName;
        newItem = new QListWidgetItem(tr(listTitle.c_str()), this);
        newItem->setData(Qt::UserRole, it->id);

        if(selected && (it->id == selected))
        {
            selectedItem = newItem;
            setCurrentItem(selectedItem, QItemSelectionModel::SelectCurrent);
        }
        
    } 
    
}        

void QtContactList::refreshContactList()
{
    Contact::ContactId selectionToRetain = getSelectedContactId(); 

    clear();
    populateList(selectionToRetain);

}

void QtContactList::dispatchListItemContactId()
{
    Contact::ContactId selectedItemId = getSelectedContactId(); 

    emit contactSelected(selectedItemId);
}

Contact::ContactId QtContactList::getSelectedContactId()
{
    Contact::ContactId selectedContactId = Contact::INVALID_ID;
    
    QListWidgetItem *selectedItem = currentItem();
    
    if(selectedItem)
    {
        //Take the first element of the list because we only allow single selection
        selectedContactId = selectedItem->data(Qt::UserRole).toUInt();
    }
    
    return selectedContactId;
}


Contact ::ContactId QtContactList :: searchList(std:: string name)
{
  QMessageBox errormessage;
  std::string nameforsearching = name;

  Contact :: ContactRecordSet allcontacts;
  dataSource.getAllContacts(allcontacts);
  Contact::ContactRecordSet::const_iterator contactrecordsetIterator;
for (contactrecordsetIterator = allcontacts.begin();contactrecordsetIterator!= allcontacts.end();contactrecordsetIterator++)
    {
      std::transform(nameforsearching.begin(), nameforsearching.end(), nameforsearching.begin(), std::ptr_fun<int, int>(std::tolower));
      std :: string ListItemfirstName = contactrecordsetIterator->firstName.c_str();
      std::transform(ListItemfirstName.begin(), ListItemfirstName.end(), ListItemfirstName.begin(), std::ptr_fun<int, int>(std::tolower));
      if((nameforsearching)==(ListItemfirstName))
    {
        Contact::ContactId searchcontactid =contactrecordsetIterator ->id;
        return searchcontactid ;

}
}

       errormessage.setText("No such Contact");
       errormessage.exec();

}
