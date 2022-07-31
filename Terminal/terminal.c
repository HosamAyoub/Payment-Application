/********************************************************************************************/
/********************************************************************************************/
/********************			Author: Hosam Ayoub			*********************************/
/********************			Layer: Terminal				*********************************/
/********************************************************************************************/
/********************************************************************************************/
#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    time_t seconds = time(NULL);
    struct tm *currentDate = localtime(&seconds);
    uint16_t year = (currentDate->tm_year + 1900);
    termData->transactionDate[0] = currentDate->tm_mday / 10 + '0';
    termData->transactionDate[1] = currentDate->tm_mday % 10 + '0';
    termData->transactionDate[2] = '/';

    termData->transactionDate[3] = (currentDate->tm_mon + 1) / 10 + '0';
    termData->transactionDate[4] = (currentDate->tm_mon + 1) % 10 + '0';
    termData->transactionDate[5] = '/';

    for (uint8_t yearIndex = 9; yearIndex > 5; yearIndex--)
    {
        termData->transactionDate[yearIndex] = year % 10 + '0';
        year /= 10;
    }
    termData->transactionDate[10] = '\0';

    // printf("Enter the transaction data as DD/MM/YYYY: ");
    // scanf(" %[^\n]*c", &termData->transactionDate);
    if (strlen(termData->transactionDate) != 10 || termData->transactionDate == NULL ||
        isdigit(termData->transactionDate[0]) == 0 || isdigit(termData->transactionDate[1]) == 0 ||
        termData->transactionDate[2] != '/' || isdigit(termData->transactionDate[3]) == 0 ||
        isdigit(termData->transactionDate[4]) == 0 || termData->transactionDate[5] != '/' ||
        isdigit(termData->transactionDate[6]) == 0 || isdigit(termData->transactionDate[7]) == 0 ||
        isdigit(termData->transactionDate[8]) == 0 || isdigit(termData->transactionDate[9]) == 0)
    {
        return WRONG_DATE;
    }
    return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    if (cardData.cardExpirationDate[EXPIRATION_DECADE] == termData.transactionDate[TRANSACTION_DECADE])
    {
        if (cardData.cardExpirationDate[EXPIRATION_YEAR] == termData.transactionDate[TRANSACTION_YEAR])
        {
            if (cardData.cardExpirationDate[EXPIRATION_TENS_MONTHS] == termData.transactionDate[TRANSACTION_TENS_MONTHS])
            {
                if (cardData.cardExpirationDate[EXPIRATION_MONTH] == termData.transactionDate[TRANSACTION_MONTH])
                {
                    return TERMINAL_OK;
                }
                else if (cardData.cardExpirationDate[EXPIRATION_MONTH] < termData.transactionDate[TRANSACTION_MONTH])
                {
                    return EXPIRED_CARD;
                }
            }
            else if (cardData.cardExpirationDate[EXPIRATION_TENS_MONTHS] < termData.transactionDate[TRANSACTION_TENS_MONTHS])
                return EXPIRED_CARD;
        }
        else if (cardData.cardExpirationDate[EXPIRATION_YEAR] < termData.transactionDate[TRANSACTION_YEAR])
            return EXPIRED_CARD;
    }
    else if (cardData.cardExpirationDate[EXPIRATION_DECADE] < termData.transactionDate[TRANSACTION_DECADE])
    {
        return EXPIRED_CARD;
    }
    return TERMINAL_OK;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
    uint8_t primaryAccountNumberIndex = 0, sum = 0, primaryAccountNumber = 0;
    for (uint8_t iterator = 0; iterator < sizeof(cardData->primaryAccountNumber); iterator++)
    {
        if (cardData->primaryAccountNumber[iterator] >= '0' && cardData->primaryAccountNumber[iterator] <= '9')
        {
            // Convert the char to its number
            primaryAccountNumber = cardData->primaryAccountNumber[iterator] - '0';
            if (primaryAccountNumberIndex % 2 == 0)
            {
                if (primaryAccountNumber * 2 > 9)
                {
                    sum += (primaryAccountNumber * 2) / 10;
                    sum += (primaryAccountNumber * 2) % 10;
                }
                else
                {
                    sum += primaryAccountNumber * 2;
                }
            }
            else if (primaryAccountNumberIndex % 2 == 1)
            {
                sum += primaryAccountNumber;
            }
            primaryAccountNumberIndex++;
        }
    }
    if (sum % 10 == 0)
    {
        return TERMINAL_OK;
    }
    return INVALID_CARD;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    printf("Enter the transaction amount: ");
    scanf("%f", &termData->transAmount);
    if (termData->transAmount <= 0)
    {
        return INVALID_AMOUNT;
    }
    return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    setMaxAmount(termData);
    if (termData->transAmount > termData->maxTransAmount)
    {
        return EXCEED_MAX_AMOUNT;
    }
    return TERMINAL_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    termData->maxTransAmount = MAXIMUM_TRANSACTION_AMOUNT;
}