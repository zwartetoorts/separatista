set reader = CreateObject("Separatista.DocumentReader")

if reader.ReadDocument("C:\Users\Okkel\Documents\Visual Studio 2013\Projects\Separatista\doc\BNG SEPA SDD 008_001_ 02 voorbeeld.XML") = 0 then
	w = 0
end if


Set doc = CreateObject("Separatista.MT940SDocument")
    
If doc.Open("C:\Users\Okkel\Downloads\MT940.swi") = 0 Then
	WScript.Echo "Number of documents:" & doc.RecordsetCount

	For Each rs In doc
		WScript.Echo "*************************** New Recordset"
		WScript.Echo "CurrencyClient: " & rs.CurrencyClient
		WScript.Echo "Transaction reference: " & rs.TransactionReference
		WScript.Echo "Serial Number: " & rs.SerialNumber
		WScript.Echo "Client IBAN: " & rs.IBANClient.IBAN
		WScript.Echo "Previous Balance: " & FormatCurrency(rs.PreviousBalance)
		WScript.Echo "Previous Balance Date:  " & FormatDateTime(rs.PreviousBalanceDate, 1)
		WScript.Echo "Current Balance: " & FormatCurrency(rs.CurrentBalance)
		WScript.Echo "Current Balance Date:  " & FormatDateTime(rs.CurrentBalanceDate, 1)
		rs.MoveFirst
		
		do while not rs.EOF 
			WScript.Echo Chr(9) & "********************************** New Transaction"
			WScript.Echo Chr(9) & "Transaction Date: " & FormatDateTime(rs.TransactionDate, 1)
			WScript.Echo Chr(9) & "RDC Code: " & rs.RDCCode
			WScript.Echo Chr(9) & "Currency: " & FormatCurrency(rs.Currency)
			WScript.Echo Chr(9) & "Transaction code: " & rs.TransactionCode
			WScript.Echo Chr(9) & "Transaction reference:  " & rs.TransactionRef
			WScript.Echo Chr(9) & "Foreign IBAN: " & rs.ForeignIBAN.IBAN
			
			WScript.Echo Chr(9) & Chr(9) & "********************************** New Description"
			for each key in rs
				WScript.Echo Chr(9) & Chr(9) & key & "=>" & rs.Description(key)
			next
			
			rs.MoveNext
		loop
		WScript.Echo ""
    Next
Else
    WScript.Echo "Parser error"
End If
  
if Err.Number <> 0 then
	WScript.Echo Err.Description
End if
