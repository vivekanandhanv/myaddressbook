#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include "qtcontactform.h"



QtContactForm::QtContactForm(QWidget *parent) : 
        QFormLayout(parent), firstNameField(new QLineEdit()),
        lastNameField(new QLineEdit()),
        addressField(new QLineEdit()),
        phoneNumberField(new QLineEdit()),
        emailField(new QLineEdit()),
        DOBField(new QLineEdit())
{
    addRow("First Name", firstNameField);
    addRow("Last Name", lastNameField);
    addRow("Address", addressField);
    addRow("Phone Number", phoneNumberField);
    addRow("Email", emailField);
    addRow("DOB", DOBField);
}

void QtContactForm::clear()
{
    firstNameField->setText("");
    lastNameField->setText("");
    addressField->setText("");
    phoneNumberField->setText("");
    emailField->setText("");
    DOBField->setText("");               \
}
