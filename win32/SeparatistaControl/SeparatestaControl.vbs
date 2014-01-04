set reader = CreateObject("Separatista.DocumentReader")
set ddoc = CreateObject("Separatista.DirectDebitDocument")



if reader.ReadDocument("C:\Users\Okkel\Documents\Visual Studio 2013\Projects\Separatista\doc\BNG SEPA SDD 008_001_ 02 voorbeeld.XML") = 0 then
	w = 0
end if


