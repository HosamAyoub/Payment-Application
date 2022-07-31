/********************************************************************************************/
/********************************************************************************************/
/********************			Author: Hosam Ayoub			*********************************/
/********************			Layer: Server				*********************************/
/********************************************************************************************/
/********************************************************************************************/
#include "server.h"

static float currentBalance;

// Assuming these samples
ST_accountsDB_t accountsDataBase[255] = {{342342.5, "4847 3529 8926 3094"},
                                         {82365.423, "3379 5135 6110 8795"},
                                         {9435, "4904 8398 2248 5959"},
                                         {3463, "2769 1483 0405 9987"},
                                         {42938, "1234 5678 9876 5432"},
                                         {12938, "9131 4617 8375 9183"},
                                         {31295.7, "0490 9912 9683 4267"}};

ST_transaction_t transactionsDataBase[255] = {{0, 0, 0, 0}};

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    transData->transState = APPROVED;
    if (isValidAccount(&transData->cardHolderData) == DECLINED_STOLEN_CARD)
    {
        transData->transState = DECLINED_STOLEN_CARD;
    }
    else if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
    {
        transData->transState = DECLINED_INSUFFECIENT_FUND;
    }
    else if (saveTransaction(transData) == SAVING_FAILED)
    {
        transData->transState = INTERNAL_SERVER_ERROR;
    }
    else if (transData->transState == APPROVED)
    {
        // Update balance
        uint8_t index = 0;
        while (*(accountsDataBase[index].primaryAccountNumber) != 0)
        {
            if (strcmp(transData->cardHolderData.primaryAccountNumber, accountsDataBase[index].primaryAccountNumber) == 0)
            {
                printf("Your old balance was: %.2f\n", accountsDataBase[index].balance);
                accountsDataBase[index].balance -= transData->terminalData.transAmount;
                printf("Your new balance is: %.2f\n", accountsDataBase[index].balance);
                break;
            }
            index++;
        }
    }
    return transData->transState;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
    uint8_t index = 0;
    while (*(accountsDataBase[index].primaryAccountNumber) != 0)
    {
        if (strcmp(cardData->primaryAccountNumber, accountsDataBase[index].primaryAccountNumber) == 0)
        {
            // Saved the balance in a buffer so that I can use it in isAmountAvailable
            currentBalance = accountsDataBase[index].balance;
            return SERVER_OK;
        }
        index++;
    }
    return DECLINED_STOLEN_CARD;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    if (termData->transAmount < currentBalance)
    {
        return SERVER_OK;
    }
    return LOW_BALANCE;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    static uint8_t index = 0;
    static uint32_t sequenceNumber = 1;
    if (index < sizeof(transactionsDataBase) / sizeof(ST_transaction_t))
    {
        transData->transactionSequenceNumber = sequenceNumber;
        transactionsDataBase[index].cardHolderData = transData->cardHolderData;
        transactionsDataBase[index].terminalData = transData->terminalData;
        transactionsDataBase[index].transState = transData->transState;
        transactionsDataBase[index].transactionSequenceNumber = transData->transactionSequenceNumber;
        printf("Transaction sequence number: %d\n", transactionsDataBase[index].transactionSequenceNumber);
        sequenceNumber++;
        index++;
        return TERMINAL_OK;
    }
    return SAVING_FAILED;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
    uint8_t start = 0, end = 0, middle, iterator = 0;
    sint8_t index = -1;
    // binary search
    while (transactionsDataBase[end].transactionSequenceNumber != 0)
    {
        end++;
    }
    middle = (start + end) / 2;
    while (start <= end)
    {
        if (transactionSequenceNumber == transactionsDataBase[middle].transactionSequenceNumber)
        {
            index = middle;
            break;
        }
        if (transactionSequenceNumber > transactionsDataBase[middle].transactionSequenceNumber)
        {
            start = middle + 1;
        }
        else if (transactionSequenceNumber < transactionsDataBase[middle].transactionSequenceNumber)
        {
            end = middle - 1;
        }
        middle = (start + end) / 2;
    }

    // Check if the value of search was found or not
    if (index == -1)
    {
        printf("Not found!\n");
        return TRANSACTION_NOT_FOUND;
    }
    else
    {
        printf("transaction sequence number: %d\n", transactionsDataBase[index].transactionSequenceNumber);
        printf("%s\n",transactionsDataBase[index].terminalData.transactionDate);
        printf("%.2f\n",transactionsDataBase[index].terminalData.transAmount);
        return SERVER_OK;
    }
}