
# When everybody is watching
----------------------------------

Noémie Carrier & Thomas Rompré
Final project proposal

CART 360 TANGIBLE MEDIA & PHYSICAL COMPUTING
Concordia University, Faculty of Fine Arts, Department of Design & Computation Arts

## Project description
---------------------------------

“When Everybody is watching” is a wearable art piece that covers the wearer’s face, utilizing a variety of biosensors to gauge the emotional state of the wearer and to react accordingly. This dynamic response includes displaying a neutral facade if the wearer is feeling fearful or anxious, obstructing the view in cases of anger to take a breather, providing more visibility when the wearer is happy, and giving a subtle pressure to strengthen the shoulders to encourage more confidence for those feeling shy. The mask will integrate some textile actuators, revealing and hiding different parts, and different motors to change the shape.

The mask will offer a temporary persona for the user, one that they can manipulate with their biometric data. It is intended to be an experience that a variety of people can try, by wearing the piece and immersing themselves in different everyday scenarios such as reading and listening to music to bring out different outputs from the mask. 

The aim of the object is to make the wearer and the audience feel some kind of curiosity. It will be inspired by the work of different artists working in the field of privacy, more specifically those abstract face covers to blur facial recognition softwares. By observing the mask’s different responses, users will be encouraged to play with their level of emotions, calm, and stress. This prompts reflections of the significance of such intimate proximity with an object in a day to day scenario. It leans towards exploration, since growing trust in those personas and the reactions of the adornment can be a challenge. It also raises questions about privacy and performed identities in different contexts.

By being more conscious of their biometric data, the user can reflect on how their emotions are manifested. This awareness enables users to consider that identity can express itself in a lot of different ways.

--------- 

1.The project is meant to confound and confuse recognition software and the human’s ability to recognize and associate individuals and their feature, as a comment on the intrusion of privacy and anonymity that occurs due to the omnipresence of cameras and recording devices. As a wearable, it can be worn and used at any time, but it’s core purpose is it working as a sort of countermeasure/critique against surveillance and impromptu recording of oneself.

2.For the user, it afford a new sense of anonymity, and the unique visual aspect of the mask attracts curiosity among people around him. Due to its shifting nature, however, capturing the individual’s likeliness (and coincidentally, the mask’s) becomes very difficult - read impossible - due to it constantly shifting shape, color, form , etc.

3.It helps the user remain anonymous, somewhat, and potentially could shield him from recognition software/unwanted recording should he be subject to it.

4.Facial recognition is a learning system - both on the software level and on the human level (as in, human associate faces with identity). By constantly interfering with facial appearance, we throw off that learning system. Thus somewhat protecting the user’s anonymity.

## Sensors and BOM
----------
* Inputs:
	1. Biometric sensors
		Various sensors can gather biometric information like pulse, oxygen in blood, airflow, body temperature, ECG, glucometer, galvanic skin response, blood pressure, position and electromyography (muscle) sensor. Depending where they are placed on the body, they can give precious insight about the wearers emotional state.
	2. Brain waves
		Electroencephalography (EEG) records electrical activity in the brain with the help of electrodes placed on the scalp. It can give interesting data about level of concentration, calmness or stress.
* Outputs
	1. **[Motors](https://www.youtube.com/watch?v=8nMXiUyq3tg)
		1. Stepper motors (in general)
			Continuous (can do more and more turn)
			Precision in the amount of steps
			No feedback
			Require more energy
		2. Servo motor (in general)
			Simple to wire up
			Limit amount of turn
			Can be relatively small
			Feedback
			More torque
			Less energy required
	2. [Shape memory alloys](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC9919340/) (For morphing. Hot, high voltage?)
	3. [Inflatables](https://dl.acm.org/doi/fullHtml/10.1145/3472749.3474802) & Pneumatics (bulky, noisy)
	4. Electromagnets (high amp)
	5. Thermochromic ink
	6. Polymer Dispersed Liquid Crystal (PLDC) film

## Illustrations of the interaction
--------------
  
## Journey Map
------------------
![[journeyboard.png]]
## References
------------- 
### [Aposema](https://www.instructables.com/APOSEMA/) 
*Masters thesis project made by [Adi Meyer](http://www.adimeyer.com/), [Sirou Peng](https://www.siroupeng.com/) and [Silvia Rueda](https://www.silviarueda.com/portfolio), as part of the [interactive architecture lab](http://www.interactivearchitecture.org/) in the Bartlett, supervised by [Yuri Suzuki](http://yurisuzuki.com/) and [Ruairi Glynn,](http://www.ruairiglynn.co.uk/) 2017*
	Using muscle sensors and an inflatable system, they created a silicone mask that reacts to the wearer's facial expressions

### [Printed Paper Actuator](https://www.morphingmatter.cs.cmu.edu/projects/printed-paper-actuator)
*By Guanyun Wang, Tingyu Cheng, Youngwook Do, Humphrey Yang, Ye Tao, Jianzhe Gu, Byoungkwon An, Lining Yao from the morphing matter lab 2018* 
	Book using simple paper actuator that they developed. It is interesting to see how electronics can be concealed on a simple material like paper to generate movement.

### [Surveillance Exclusion](http://www.jipvanleeuwenstein.nl/)
by Jip Van Leeuenstein
### [Privacy Visor](https://slate.com/technology/2013/01/isao-echizen-and-seiichi-gohshi-s-privacy-visor-shields-you-from-facial-recognition-technology-photo.html)
by Isao Echizen’s 

Zach Blas’ Facial Weaponisation Suite https://zachblas.info/works/facial-weaponization-suite/
    Inspirations for the physical aspect of the mask.

Most of these project are simply practical in form - a lot of it coming straight out of the HK protests made this a necessity. We also would like to add an artistic and aesthetic value to our project, as well as add some level of protection against traditional methods of recording rather than only facial recognition software (like someone taking a picture of you without your knowing in public, and such).



-------------------------------
Week 1:
Our choice stopped at servo motors for output, and muscle sensor for input. We also bought electromagnet coil, to experiment with it and have another option of output. Research is still going on to define the form of the prototype.
Week 2:
While exploring compliant linear mechanisms and ways to amplify a linear movement, I stumbled across a video about preprogrammed curved surfaces https://www.youtube.com/watch?v=JeOrhh6shS8. It will be our base structure to which we can add more outputs to our liking. This week, I will print out different variants of the material, to figure which one requires the less physical compression to do the biggest positive curvature. Thomas will make sure that we have a working input from the muscle sensor.
Week 3: PRESENTATION OF THE PROTOTYPE