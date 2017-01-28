#!/usr/bin/python
import sys, string, locale
from optparse import OptionParser

class compare:
    def __init__(self,file1, file2):
		try:
			if file1 == "-":
				f1 = sys.stdin
				f2 = open(file2, 'r')
			elif file2 == "-":
				f2 = sys.stdin
				f1 = open(file1, 'r')
			elif file1 == "-" and file2 == "-":
				print("Error: Only one file can be provided through STDIN")
				exit()
			else:
				f1 = open(file1, 'r')
				f2 = open(file2, 'r')
			self.lines1 = f1.read().split('\n')
			self.lines2 = f2.read().split('\n')
			del self.lines1[len(self.lines1)-1]
			del self.lines2[len(self.lines2)-1]
			self.col1 = []
			self.col2 = []
			self.col3 = []
			f1.close()
			f2.close()
		except IOError as e:
			parser = OptionParser()
			parser.error("IO error({0}): {1}".
						  format(e.errno, e.strerror))
    def startit(self):

		print(self.lines1)
		print(self.lines2)
		firstcount = 0
		secondcount = 0


		while(firstcount < len(self.lines1) and secondcount < len(self.lines2)):
			if self.lines1[firstcount] > self.lines2[secondcount]:
				found = False
				word1 = self.lines2[0]
				print(word1)
				for word2 in self.lines1:
					if word1 == word2:
						found = True
						self.col3.append(word1)
						self.col1.append("")
						self.col2.append("")
						self.lines2 = [x for x in self.lines2 if x != word1]
						self.lines1 = [x for x in self.lines1 if x != word1]

				if found == False:
					self.col1.append("")
					self.col2.append(word1)
					self.col3.append("")
					self.lines2 = [x for x in self.lines2 if x != word1]
					print(self.lines2)

			else:
				found=False
				word1 = self.lines1[firstcount]
				print(word1)
				for word2 in self.lines2:
					if word1 == word2:
						found=True
						self.col3.append(word1)
						self.col1.append("")
						self.col2.append("")
						self.lines2 = [x for x in self.lines2 if x != word1]
						self.lines1 = [x for x in self.lines1 if x != word1]

				if found == False:
					self.col1.append(word1)
					self.col2.append("")
					self.col3.append("")
					self.lines1 = [x for x in self.lines1 if x != word1]
					print(self.lines1)

		while(self.lines1 != []):
			word12 = self.lines1[firstcount]
			self.col1.append(word12)
			self.col2.append("")
			self.col3.append("")
			self.lines1 = [x for x in self.lines1 if x != word12]

		while(self.lines2 != []):
			print("print the rest of lines2 here")
			word21 = self.lines2[firstcount]
			self.col2.append(word21)
			self.col1.append("")
			self.col3.append("")
			self.lines2 = [x for x in self.lines1 if x != word21]

		print(self.col1)






def main():
	locale.setlocale(locale.LC_ALL, 'C')
	version_msg = "%prog 1.0"
	usage_msg = """%prog [OPTION]... FILE1 FILE2

	Output the comparison results between FILE1 and FILE2 in three columns."""

	parser = OptionParser(version=version_msg, usage=usage_msg)
	parser.add_option("-1", action="store_true", dest="sup1",
					  default = False,
					  help="suppress column 1 (lines unique to FILE1)")
	parser.add_option("-2", action="store_true", dest="sup2",
					  default = False,
					  help="suppress column 2 (lines unique to FILE2)")
	parser.add_option("-3", action="store_true", dest="sup3",
					  default = False,
					  help="suppress column 3 (lines that appear in both files)")
	parser.add_option("-u", action="store_true", dest="unsort",
					  default = False,
					  help="run comparison on unsorted files line by line." )
	options, args = parser.parse_args(sys.argv[1:])
	try:
		sup1 = bool(options.sup1)
		sup2 = bool(options.sup2)
		sup3 = bool(options.sup3)
		unsort = bool(options.unsort)
	except:
		parser.error("Invalid option type: {0}".
					format(options.sup1))
	if len(args) != 2:
		parser.error("Missing option arguments")
	try:
		comparee = compare(args[0], args[1])
		if unsort:
			print("add implementation for unsorted file")
			comparee.startit()
		else:
			print("add implementation for sorted file")
        	comparee.startit()
		print("actually print the lists now")
	except IOError as e:
		parser.error("I/O error({0}): {1}".format(e.errno, e.strerror))

if __name__ == "__main__":
	main()
