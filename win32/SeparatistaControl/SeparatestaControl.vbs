set iban = CreateObject("Separatista.IBAN")
iban.IBAN = "nl67rabo0163311250"
wscript.echo iban.IBAN
wscript.echo iban.Check

set doc = CreateObject("Separatista.CustomerDirectDebitInitiation")

doc.MessageIdentification = "0001"
wscript.echo doc.MessageIdentification
doc.CreationDateTime = now()
wscript.echo doc.CreationDateTime
wscript.echo doc.NumberOfTransactions


WScript.StdIn.Read(1)
