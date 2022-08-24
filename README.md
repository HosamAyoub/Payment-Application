# PaymentApplication
Payment systems are now available everywhere and everyone interacts with these systems every day.  
There are different types of transactions you can make, SALE, REFUND, Pre-Authorization, and VOID.

* SALE: means to buy something and its price will be deducted from your bank account.
* REFUND: this means that you will return something and wants your money back to your bank account.
* Pre-Authorization: means holding an amount of money from your account, e.g Hotel reservation.
* VOID: this means canceling the transaction, e.g if the seller entered the wrong amount.  

Implemented the SALE transaction only by simulating the card, terminal(ATM), and the server.  

## The project can be distributed over 6 main tasks:

<img src="https://github.com/HosamAyoub/Photos/blob/main/PaymentApplication/payment-flowchart.jpeg?raw=true" title = "System flow chart"> 

### Development environment preparation
1. Create modules folders.
2. Create .c and .h file for each module.
3. Add header file guard.
4. Create the main.c file.

### Card module
1. Fill in card.h file with functions' prototypes and typedefs.
2. Implement getCardHolderName function.
3. Implement getCardExpiryDate function.
4. Implement getCardPAN function.

### Terminal module
1. Fill in terminal.h file with functions' prototypes and typedefs.
2. Implement getTransactionDate function.
3. Implement isCardExpried function.
4. Implement gatTransactionAmount function.
5. Implement isBelowMaxAmount function.
6. Implement setMaxAmount function.

### Server module
1. Fill in server.h file with functions' prototypes and typedefs.
2. Implement server-side accounts' database.
3. Implement server-side transactions' database.
4. Implement recieveTransactionData function.
5. Implement isValidAccount function.
6. Implement isAmountAvailable function.
7. Implement saveTransaction function.

### Application
1. Fill in application.h file with functions' prototypes
2. Implement appStart function

### Testing
1. Transaction approved user story
2. Exceed the maximum amount user story
3. Insufficient fund user story
4. Expired card user story
5. Invalid card user story