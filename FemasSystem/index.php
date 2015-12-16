<html>
<body>
here's the initial version:

$.ajax({
	url: 'http://www.cnmooc.org/examSubmit/2230/getExamPaper-' + sid + '.mooc',
	data: {
		testPaperId: tpi,
		paperId: ppi,
		limitTime: -60,
		modelType: 'practice',
		examQuizNum: eqn,
		curSubmitNum: csn,
	},
	type: 'POST',
	dataType: 'json',
	success: function(data) {
		var answer = '';
		for (i in data.paper.paperStruct)
		{
			var quizid = i + 1;
			quiz = data.paper.paperStruct[i].quiz;
			optionid = quiz.quizResponses[0].optionId;
			array = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'];
			quizanswer = array[optionid - quiz.quizOptionses[0].optionId];
			answer += quizanswer;
		}
		$('.sup-title').html(answer);
	}
});
a = function() { 
	$.ajax({

	});
}

------------------------------------------------------------------------------------
and uglified version for test:

$.ajax({url:'http://www.cnmooc.org/examSubmit/2161/getExamPaper-.mooc',data:{testPaperId:11256,paperId:2485,limitTime:-60,modelType:'practice',examQuizNum:15,curSubmitNum:0,},type:'POST',dataType:'json',success:function(data){answer='';for(i in data.paper.paperStruct){varquizid=i+1;quiz=data.paper.paperStruct[i].quiz;optionid=quiz.quizResponses[0].optionId;array=['A','B','C','D','E','F','G','H','I'];quizanswer=array[optionid-quiz.quizOptionses[0].optionId];answer+=quizanswer;}$('.sup-title').html(answer);}});


</body>
</html>
