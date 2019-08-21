import chisel3._
import chisel3.util.{Cat, MuxCase, log2Ceil}

class PositGenerator(totalBits: Int, es: Int) extends Module {
  private val base = math.pow(2, es).toInt
  private val exponentBits = log2Ceil(base * totalBits) + es + 2
  val io = IO(new Bundle {
    val sign = Input(Bool())
    val exponent = Input(SInt(exponentBits.W))
    val fraction = Input(UInt(totalBits.W))
    val posit = Output(UInt(totalBits.W))
  })

  private val exponent = Mux(io.exponent < 0.S, if (es > 0) base.asSInt() - io.exponent else 0.S - io.exponent, io.exponent).asUInt()
  private val positRegime = exponent / base.U
  private val positExponent = (exponent % base.U) (if (es > 0) es - 1 else 0, 0)

  private val positiveExponentCombinations = Array.range(0, totalBits).map(index => {
    val regimeBits = (math.pow(2, index + 2) - 2).toInt.U
    val bitsRequiredForRegime = index + 2
    val bitsRequiredForExponent = es
    val bitsRequiredForFraction = totalBits
    val usedBits = bitsRequiredForRegime + bitsRequiredForExponent + bitsRequiredForFraction
    val numberOfBitsExcludingSignBit = totalBits - 1

    var finalPosit = regimeBits
    finalPosit = if (es > 0) Cat(finalPosit, positExponent) else finalPosit
    finalPosit = Cat(finalPosit, io.fraction)
    (positRegime === index.U) -> finalPosit(usedBits - 1, usedBits - numberOfBitsExcludingSignBit)
  })

  private val negativeExponentCombinations = Array.range(1, totalBits - 1).map(index => {
    val regimeBits = 1.U((index + 1).W)
    val bitsRequiredForRegime = index + 1
    val bitsRequiredForExponent = es
    val bitsRequiredForFraction = totalBits
    val usedBits = bitsRequiredForRegime + bitsRequiredForExponent + bitsRequiredForFraction
    val numberOfBitsExcludingSignBit = totalBits - 1

    var finalPosit = regimeBits
    finalPosit = if (es > 0) Cat(finalPosit, positExponent) else finalPosit
    finalPosit = Cat(finalPosit, io.fraction)
    (positRegime === index.U) -> finalPosit(usedBits - 1, usedBits - numberOfBitsExcludingSignBit)
  })

  val posit = Mux(io.exponent >= 0.S, MuxCase(0.U, positiveExponentCombinations), MuxCase(0.U, negativeExponentCombinations))
  io.posit := Mux(posit === 0.U, Mux(io.exponent >= 0.S,math.pow(2,totalBits -1).toInt.U,0.U),Cat(io.sign, Mux(io.sign, 0.U - posit, posit)))
}