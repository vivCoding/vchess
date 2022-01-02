const express = require('express')
const path = require('path')

const app = express()

app.use(express.static(path.join(__dirname, 'public')))

app.listen(process.env.PORT || 5000, async () => {
	console.log(`Server running on port ${process.env.PORT || 8080}`)
	console.log("-----------------------")
})