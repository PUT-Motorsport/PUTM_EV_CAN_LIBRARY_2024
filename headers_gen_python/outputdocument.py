

class CanFrame:
    frameName = None
    dataType = []
    dataNames = []
    comments = []
    frequency = None
    id = None

class CustomEnum:
    name = None
    states = []
    comments = []
class OutputDocument:
    __performIllegalCharsCheck = None
    __fileName = None

    def __init__(self,genFileName,performCheck):
        self.__performIllegalCharsCheck = performCheck
        self.__fileName = genFileName
        self.__fileName = self.__fileName.replace('.csv','.hpp')

        __file = open(self.__fileName, 'w')


