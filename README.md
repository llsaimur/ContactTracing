# ContactTracing

Implement a a data structure called "ContactTree" that will manage information about contacts between individuals.
	-ContactTree class is a blueprint for creating contacts tree objects
	-TreeNode class represents each node in the contact tree and contains patient information and a list of their direct contacts

Functionalities:
	-Adding Contacts: You can add a person to the contact tree and specify their direct contacts.
	-Deleting Contacts: You can remove a person and all their direct and indirect contacts from the tree.
	-Searching Contacts: You can look up a person's information by their unique identifier.
	-Displaying Information: You can display information about a person, their direct contacts, or the entire contact tree.
	-Tracing Infections: You can trace the source of infection by following the chain of contacts backward from an infected individual.
	-Size and Status: You can check the size of the contact tree and whether it's empty.

Implementation:
	Used queue as the linear data structure into which elements are inserted and from which they are retrived,
	use breadth-first search algorithm to traverse the contact tree efficiently.