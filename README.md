# **Arbitrary Precision Calculator (APC)**

## 📝 **Project Brief**

The Arbitrary Precision Calculator (APC) is a C-based project designed to perform mathematical operations on integers far beyond the limits of standard data types. By storing each digit in a linked list, APC enables precise computation of very large numbers. It implements addition, subtraction, multiplication, and division through manual digit-by-digit algorithms, showcasing strong data-structure handling, modular programming, and low-level memory manipulation.

---

## 📁 **Project Structure**

```
APC/
│── types.h      # Defines node structure & datatype used for big numbers
│── APC.h        # Function declarations for APC operations
│── APC.c        # Core logic implementing arithmetic on linked lists
│── main.c       # Driver code to test arithmetic functions
│── README.md    # Project documentation
```

---

## ⚙️ **Technologies Used**

* **C Programming**
* **Linked Lists**
* **Modular Arithmetic Logic**
* **Dynamic Memory Management**

---

## 🚀 **Key Features**

* Handles **very large integers** without data-type overflow
* Supports **addition, subtraction, multiplication, division**
* Uses **singly linked lists** to represent numbers and process them digit-by-digit
* Fully modular code with clean separation between logic and interface

---

## 🧠 **Challenges & Learnings**

* Designing a reliable **linked-list-based number system** for arbitrary precision
* Implementing **accurate division logic**, the most complex operation in APC
* Deepening understanding of **linked lists, string manipulation, and manual arithmetic algorithms**

---

## ▶️ **How to Run**

```
gcc APC.c main.c -o APC
./APC
```

---

## 💡 **Use Cases**

* Learning big-number arithmetic
* Understanding linked-list-based number systems
* Practicing modular C programming and file organization

---

