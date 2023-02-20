class testClass

	int thisVar,otherVar,someVar

end 

class myClass > testClass

	int testVar

	method void Check()

	end 

end 

class otherClass

	method void Other()

		myClass.thisVar = 25
		myClass.otherVar = 30

	end 


end 