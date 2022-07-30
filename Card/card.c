/********************************************************************************************/
/********************************************************************************************/
/********************			Author: Hosam Ayoub			*********************************/
/********************			Layer: Card					*********************************/
/********************************************************************************************/
/********************************************************************************************/
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    printf("Enter the cardholder's name: ");
    scanf(" %[^\n]*c", &cardData->cardHolderName);
    if (strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24 ||
        cardData->cardHolderName == NULL)
    {
        return WRONG_NAME;
    }
    return CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    printf("Enter the card expiry date as MM/YY: ");
    scanf(" %[^\n]*c", &cardData->cardExpirationDate);
    if (strlen(cardData->cardExpirationDate) != 5 || cardData->cardExpirationDate == NULL ||
        isdigit(cardData->cardExpirationDate[0]) == 0 || isdigit(cardData->cardExpirationDate[1]) == 0 ||
        cardData->cardExpirationDate[2] != '/' || isdigit(cardData->cardExpirationDate[3]) == 0 ||
        isdigit(cardData->cardExpirationDate[4]) == 0)
    {
        return WRONG_EXP_DATE;
    }
    return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    printf("Enter the card's Primary Account Number: ");
    scanf(" %[^\n]*c", &cardData->primaryAccountNumber);
    if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19 ||
    cardData->primaryAccountNumber == NULL)
    {
        return WRONG_PAN;
    }
    return CARD_OK;
}